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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_msg {int dummy; } ;
struct tipc_media_addr {int dummy; } ;
struct TYPE_6__ {struct link* buf; } ;
struct link {int checkpoint; int next_out_no; int /*<<< orphan*/  abort_limit; int /*<<< orphan*/  continuity_interval; int /*<<< orphan*/  tolerance; int /*<<< orphan*/  link_list; int /*<<< orphan*/  timer; TYPE_3__ print_buf; int /*<<< orphan*/  owner; int /*<<< orphan*/  waiting_ports; int /*<<< orphan*/  priority; int /*<<< orphan*/  addr; struct tipc_msg* pmsg; int /*<<< orphan*/  proto_msg; int /*<<< orphan*/  state; struct bearer* b_ptr; int /*<<< orphan*/  media_addr; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct bearer {int /*<<< orphan*/  links; TYPE_2__* media; int /*<<< orphan*/  priority; int /*<<< orphan*/  identity; TYPE_1__ publ; } ;
struct TYPE_5__ {int /*<<< orphan*/  window; int /*<<< orphan*/  tolerance; } ;
typedef  int /*<<< orphan*/  Handler ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INT_H_SIZE ; 
 scalar_t__ LINK_LOG_BUF_SIZE ; 
 int /*<<< orphan*/  LINK_PROTOCOL ; 
 int /*<<< orphan*/  RESET_MSG ; 
 int /*<<< orphan*/  RESET_UNKNOWN ; 
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  k_init_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  kfree (struct link*) ; 
 char* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 struct link* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_init_max_pkt (struct link*) ; 
 int /*<<< orphan*/  link_reset_statistics (struct link*) ; 
 int /*<<< orphan*/  link_set_supervision_props (struct link*,int /*<<< orphan*/ ) ; 
 scalar_t__ link_timeout ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct tipc_media_addr const*,int) ; 
 scalar_t__ msg_data (struct tipc_msg*) ; 
 int /*<<< orphan*/  msg_init (struct tipc_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_bearer_id (struct tipc_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_set_session (struct tipc_msg*,int) ; 
 int /*<<< orphan*/  msg_set_size (struct tipc_msg*,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,int,int,char*,int,int,int) ; 
 char* strchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int tipc_cluster (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  tipc_k_signal (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tipc_link_set_queue_limits (struct link*,int /*<<< orphan*/ ) ; 
 scalar_t__ tipc_link_start ; 
 int tipc_node (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  tipc_node_attach_link (struct link*) ; 
 int /*<<< orphan*/  const tipc_own_addr ; 
 int /*<<< orphan*/  tipc_printbuf_init (TYPE_3__*,char*,scalar_t__) ; 
 int tipc_random ; 
 int tipc_zone (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  warn (char*) ; 

struct link *tipc_link_create(struct bearer *b_ptr, const u32 peer,
			      const struct tipc_media_addr *media_addr)
{
	struct link *l_ptr;
	struct tipc_msg *msg;
	char *if_name;

	l_ptr = kzalloc(sizeof(*l_ptr), GFP_ATOMIC);
	if (!l_ptr) {
		warn("Link creation failed, no memory\n");
		return NULL;
	}

	if (LINK_LOG_BUF_SIZE) {
		char *pb = kmalloc(LINK_LOG_BUF_SIZE, GFP_ATOMIC);

		if (!pb) {
			kfree(l_ptr);
			warn("Link creation failed, no memory for print buffer\n");
			return NULL;
		}
		tipc_printbuf_init(&l_ptr->print_buf, pb, LINK_LOG_BUF_SIZE);
	}

	l_ptr->addr = peer;
	if_name = strchr(b_ptr->publ.name, ':') + 1;
	sprintf(l_ptr->name, "%u.%u.%u:%s-%u.%u.%u:",
		tipc_zone(tipc_own_addr), tipc_cluster(tipc_own_addr),
		tipc_node(tipc_own_addr),
		if_name,
		tipc_zone(peer), tipc_cluster(peer), tipc_node(peer));
		/* note: peer i/f is appended to link name by reset/activate */
	memcpy(&l_ptr->media_addr, media_addr, sizeof(*media_addr));
	l_ptr->checkpoint = 1;
	l_ptr->b_ptr = b_ptr;
	link_set_supervision_props(l_ptr, b_ptr->media->tolerance);
	l_ptr->state = RESET_UNKNOWN;

	l_ptr->pmsg = (struct tipc_msg *)&l_ptr->proto_msg;
	msg = l_ptr->pmsg;
	msg_init(msg, LINK_PROTOCOL, RESET_MSG, INT_H_SIZE, l_ptr->addr);
	msg_set_size(msg, sizeof(l_ptr->proto_msg));
	msg_set_session(msg, (tipc_random & 0xffff));
	msg_set_bearer_id(msg, b_ptr->identity);
	strcpy((char *)msg_data(msg), if_name);

	l_ptr->priority = b_ptr->priority;
	tipc_link_set_queue_limits(l_ptr, b_ptr->media->window);

	link_init_max_pkt(l_ptr);

	l_ptr->next_out_no = 1;
	INIT_LIST_HEAD(&l_ptr->waiting_ports);

	link_reset_statistics(l_ptr);

	l_ptr->owner = tipc_node_attach_link(l_ptr);
	if (!l_ptr->owner) {
		if (LINK_LOG_BUF_SIZE)
			kfree(l_ptr->print_buf.buf);
		kfree(l_ptr);
		return NULL;
	}

	k_init_timer(&l_ptr->timer, (Handler)link_timeout, (unsigned long)l_ptr);
	list_add_tail(&l_ptr->link_list, &b_ptr->links);
	tipc_k_signal((Handler)tipc_link_start, (unsigned long)l_ptr);

	dbg("tipc_link_create(): tolerance = %u,cont intv = %u, abort_limit = %u\n",
	    l_ptr->tolerance, l_ptr->continuity_interval, l_ptr->abort_limit);

	return l_ptr;
}