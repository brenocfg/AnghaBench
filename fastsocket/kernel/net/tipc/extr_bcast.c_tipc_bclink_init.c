#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* media; int /*<<< orphan*/  cong_links; } ;
struct TYPE_11__ {int /*<<< orphan*/  lock; } ;
struct TYPE_13__ {int next_out_no; int /*<<< orphan*/  print_buf; int /*<<< orphan*/  name; int /*<<< orphan*/  state; TYPE_3__* b_ptr; int /*<<< orphan*/  max_pkt; TYPE_2__* owner; int /*<<< orphan*/  waiting_ports; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; int /*<<< orphan*/  send_msg; } ;
struct TYPE_14__ {TYPE_3__ bearer; TYPE_2__ node; TYPE_4__ link; TYPE_1__ media; } ;

/* Variables and functions */
 scalar_t__ BCLINK_LOG_BUF_SIZE ; 
 int /*<<< orphan*/  BCLINK_WIN_DEFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_PKT_DEFAULT_MCAST ; 
 int /*<<< orphan*/  TIPC_MAX_LINK_NAME ; 
 int /*<<< orphan*/  WORKING_WORKING ; 
 TYPE_5__* bcbearer ; 
 TYPE_4__* bcl ; 
 TYPE_5__* bclink ; 
 int /*<<< orphan*/  kfree (TYPE_5__*) ; 
 char* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_5__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_bcbearer_send ; 
 int /*<<< orphan*/  tipc_bclink_name ; 
 int /*<<< orphan*/  tipc_link_set_queue_limits (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_printbuf_init (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  warn (char*) ; 

int tipc_bclink_init(void)
{
	bcbearer = kzalloc(sizeof(*bcbearer), GFP_ATOMIC);
	bclink = kzalloc(sizeof(*bclink), GFP_ATOMIC);
	if (!bcbearer || !bclink) {
 nomem:
		warn("Multicast link creation failed, no memory\n");
		kfree(bcbearer);
		bcbearer = NULL;
		kfree(bclink);
		bclink = NULL;
		return -ENOMEM;
	}

	INIT_LIST_HEAD(&bcbearer->bearer.cong_links);
	bcbearer->bearer.media = &bcbearer->media;
	bcbearer->media.send_msg = tipc_bcbearer_send;
	sprintf(bcbearer->media.name, "tipc-multicast");

	bcl = &bclink->link;
	INIT_LIST_HEAD(&bcl->waiting_ports);
	bcl->next_out_no = 1;
	spin_lock_init(&bclink->node.lock);
	bcl->owner = &bclink->node;
	bcl->max_pkt = MAX_PKT_DEFAULT_MCAST;
	tipc_link_set_queue_limits(bcl, BCLINK_WIN_DEFAULT);
	bcl->b_ptr = &bcbearer->bearer;
	bcl->state = WORKING_WORKING;
	strlcpy(bcl->name, tipc_bclink_name, TIPC_MAX_LINK_NAME);

	if (BCLINK_LOG_BUF_SIZE) {
		char *pb = kmalloc(BCLINK_LOG_BUF_SIZE, GFP_ATOMIC);

		if (!pb)
			goto nomem;
		tipc_printbuf_init(&bcl->print_buf, pb, BCLINK_LOG_BUF_SIZE);
	}

	return 0;
}