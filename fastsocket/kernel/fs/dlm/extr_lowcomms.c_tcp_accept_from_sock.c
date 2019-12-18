#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct socket {TYPE_2__* sk; TYPE_1__* ops; int /*<<< orphan*/  type; } ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
struct connection {int nodeid; int /*<<< orphan*/  sock_mutex; int /*<<< orphan*/  rwork; int /*<<< orphan*/  flags; void* rx_action; struct socket* sock; struct connection* othercon; int /*<<< orphan*/  swork; } ;
typedef  int /*<<< orphan*/  peeraddr ;
struct TYPE_6__ {int /*<<< orphan*/  ss_family; } ;
struct TYPE_5__ {struct connection* sk_user_data; } ;
struct TYPE_4__ {int (* accept ) (struct socket*,struct socket*,int /*<<< orphan*/ ) ;scalar_t__ (* getname ) (struct socket*,struct sockaddr*,int*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CF_IS_OTHERCON ; 
 int /*<<< orphan*/  CF_READ_PENDING ; 
 int EAGAIN ; 
 int ECONNABORTED ; 
 int ENOMEM ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  add_sock (struct socket*,struct connection*) ; 
 scalar_t__ addr_to_nodeid (struct sockaddr_storage*,int*) ; 
 int /*<<< orphan*/  con_cache ; 
 TYPE_3__** dlm_local_addr ; 
 struct connection* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_print (char*,...) ; 
 int /*<<< orphan*/  make_sockaddr (struct sockaddr_storage*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct connection* nodeid2con (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int /*<<< orphan*/  process_recv_sockets ; 
 int /*<<< orphan*/  process_send_sockets ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* receive_from_sock ; 
 int /*<<< orphan*/  recv_workqueue ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sock_create_kern (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct socket**) ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 
 int stub1 (struct socket*,struct socket*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (struct socket*,struct sockaddr*,int*,int) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tcp_accept_from_sock(struct connection *con)
{
	int result;
	struct sockaddr_storage peeraddr;
	struct socket *newsock;
	int len;
	int nodeid;
	struct connection *newcon;
	struct connection *addcon;

	memset(&peeraddr, 0, sizeof(peeraddr));
	result = sock_create_kern(dlm_local_addr[0]->ss_family, SOCK_STREAM,
				  IPPROTO_TCP, &newsock);
	if (result < 0)
		return -ENOMEM;

	mutex_lock_nested(&con->sock_mutex, 0);

	result = -ENOTCONN;
	if (con->sock == NULL)
		goto accept_err;

	newsock->type = con->sock->type;
	newsock->ops = con->sock->ops;

	result = con->sock->ops->accept(con->sock, newsock, O_NONBLOCK);
	if (result < 0)
		goto accept_err;

	/* Get the connected socket's peer */
	memset(&peeraddr, 0, sizeof(peeraddr));
	if (newsock->ops->getname(newsock, (struct sockaddr *)&peeraddr,
				  &len, 2)) {
		result = -ECONNABORTED;
		goto accept_err;
	}

	/* Get the new node's NODEID */
	make_sockaddr(&peeraddr, 0, &len);
	if (addr_to_nodeid(&peeraddr, &nodeid)) {
		log_print("connect from non cluster node");
		sock_release(newsock);
		mutex_unlock(&con->sock_mutex);
		return -1;
	}

	log_print("got connection from %d", nodeid);

	/*  Check to see if we already have a connection to this node. This
	 *  could happen if the two nodes initiate a connection at roughly
	 *  the same time and the connections cross on the wire.
	 *  In this case we store the incoming one in "othercon"
	 */
	newcon = nodeid2con(nodeid, GFP_NOFS);
	if (!newcon) {
		result = -ENOMEM;
		goto accept_err;
	}
	mutex_lock_nested(&newcon->sock_mutex, 1);
	if (newcon->sock) {
		struct connection *othercon = newcon->othercon;

		if (!othercon) {
			othercon = kmem_cache_zalloc(con_cache, GFP_NOFS);
			if (!othercon) {
				log_print("failed to allocate incoming socket");
				mutex_unlock(&newcon->sock_mutex);
				result = -ENOMEM;
				goto accept_err;
			}
			othercon->nodeid = nodeid;
			othercon->rx_action = receive_from_sock;
			mutex_init(&othercon->sock_mutex);
			INIT_WORK(&othercon->swork, process_send_sockets);
			INIT_WORK(&othercon->rwork, process_recv_sockets);
			set_bit(CF_IS_OTHERCON, &othercon->flags);
		}
		if (!othercon->sock) {
			newcon->othercon = othercon;
			othercon->sock = newsock;
			newsock->sk->sk_user_data = othercon;
			add_sock(newsock, othercon);
			addcon = othercon;
		}
		else {
			printk("Extra connection from node %d attempted\n", nodeid);
			result = -EAGAIN;
			mutex_unlock(&newcon->sock_mutex);
			goto accept_err;
		}
	}
	else {
		newsock->sk->sk_user_data = newcon;
		newcon->rx_action = receive_from_sock;
		add_sock(newsock, newcon);
		addcon = newcon;
	}

	mutex_unlock(&newcon->sock_mutex);

	/*
	 * Add it to the active queue in case we got data
	 * beween processing the accept adding the socket
	 * to the read_sockets list
	 */
	if (!test_and_set_bit(CF_READ_PENDING, &addcon->flags))
		queue_work(recv_workqueue, &addcon->rwork);
	mutex_unlock(&con->sock_mutex);

	return 0;

accept_err:
	mutex_unlock(&con->sock_mutex);
	sock_release(newsock);

	if (result != -EAGAIN)
		log_print("error accepting connection from node: %d", result);
	return result;
}