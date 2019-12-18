#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct svc_sock {struct sock* sk_sk; struct socket* sk_sock; int /*<<< orphan*/  sk_owspace; int /*<<< orphan*/  sk_odata; int /*<<< orphan*/  sk_ostate; } ;
struct svc_serv {int sv_max_mesg; } ;
struct socket {scalar_t__ type; struct sock* sk; } ;
struct sock {int /*<<< orphan*/  sk_write_space; int /*<<< orphan*/  sk_data_ready; int /*<<< orphan*/  sk_state_change; struct svc_sock* sk_user_data; int /*<<< orphan*/  sk_protocol; int /*<<< orphan*/  sk_family; } ;
struct TYPE_2__ {int /*<<< orphan*/  sport; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ SOCK_DGRAM ; 
 int SVC_SOCK_ANONYMOUS ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 TYPE_1__* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  kfree (struct svc_sock*) ; 
 struct svc_sock* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int svc_register (struct svc_serv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_sock_setbufsize (struct socket*,int,int) ; 
 int /*<<< orphan*/  svc_tcp_init (struct svc_sock*,struct svc_serv*) ; 
 int /*<<< orphan*/  svc_udp_init (struct svc_sock*,struct svc_serv*) ; 

__attribute__((used)) static struct svc_sock *svc_setup_socket(struct svc_serv *serv,
						struct socket *sock,
						int *errp, int flags)
{
	struct svc_sock	*svsk;
	struct sock	*inet;
	int		pmap_register = !(flags & SVC_SOCK_ANONYMOUS);

	dprintk("svc: svc_setup_socket %p\n", sock);
	if (!(svsk = kzalloc(sizeof(*svsk), GFP_KERNEL))) {
		*errp = -ENOMEM;
		return NULL;
	}

	inet = sock->sk;

	/* Register socket with portmapper */
	if (*errp >= 0 && pmap_register)
		*errp = svc_register(serv, inet->sk_family, inet->sk_protocol,
				     ntohs(inet_sk(inet)->sport));

	if (*errp < 0) {
		kfree(svsk);
		return NULL;
	}

	inet->sk_user_data = svsk;
	svsk->sk_sock = sock;
	svsk->sk_sk = inet;
	svsk->sk_ostate = inet->sk_state_change;
	svsk->sk_odata = inet->sk_data_ready;
	svsk->sk_owspace = inet->sk_write_space;

	/* Initialize the socket */
	if (sock->type == SOCK_DGRAM)
		svc_udp_init(svsk, serv);
	else {
		/* initialise setting must have enough space to
		 * receive and respond to one request.
		 */
		svc_sock_setbufsize(svsk->sk_sock, 4 * serv->sv_max_mesg,
					4 * serv->sv_max_mesg);
		svc_tcp_init(svsk, serv);
	}

	dprintk("svc: svc_setup_socket created %p (inet %p)\n",
				svsk, svsk->sk_sk);

	return svsk;
}