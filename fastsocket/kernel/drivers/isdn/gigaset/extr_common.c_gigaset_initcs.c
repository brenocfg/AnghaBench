#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct inbuf_t {int dummy; } ;
struct gigaset_driver {int dummy; } ;
struct TYPE_6__ {scalar_t__ expires; } ;
struct cardstate {int channels; int onechannel; int ignoreframes; int running; int gotfwver; int cidmode; TYPE_2__ timer; int /*<<< orphan*/  lock; scalar_t__ cs_init; TYPE_1__* ops; scalar_t__ cmdbytes; scalar_t__ curlen; int /*<<< orphan*/  cmdlock; int /*<<< orphan*/ * lastcmdbuf; int /*<<< orphan*/  cmdbuf; scalar_t__ isdn_up; scalar_t__ connected; void* inbuf; int /*<<< orphan*/ * bcs; scalar_t__ cbytes; scalar_t__ dle; int /*<<< orphan*/  at_state; int /*<<< orphan*/  mstate; int /*<<< orphan*/  mode; scalar_t__ waiting; int /*<<< orphan*/  waitqueue; int /*<<< orphan*/  tabcid; int /*<<< orphan*/  tabnocid; int /*<<< orphan*/ * tty_dev; int /*<<< orphan*/ * tty; int /*<<< orphan*/ * dev; scalar_t__ open_count; scalar_t__ cur_at_seq; scalar_t__ commands_pending; int /*<<< orphan*/  event_tasklet; scalar_t__ ev_head; scalar_t__ ev_tail; int /*<<< orphan*/  ev_lock; int /*<<< orphan*/  temp_at_states; } ;
struct bc_state {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* initcshw ) (struct cardstate*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_INIT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GIG_TICK ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INS_command ; 
 int /*<<< orphan*/  MS_UNINITIALIZED ; 
 int /*<<< orphan*/  M_UNKNOWN ; 
 int /*<<< orphan*/  VALID_ID ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 struct cardstate* alloc_cs (struct gigaset_driver*) ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gigaset_at_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct cardstate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gigaset_freecs (struct cardstate*) ; 
 int /*<<< orphan*/  gigaset_handle_event ; 
 int /*<<< orphan*/  gigaset_if_init (struct cardstate*) ; 
 int /*<<< orphan*/  gigaset_inbuf_init (void*,int /*<<< orphan*/ *,struct cardstate*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gigaset_init_dev_sysfs (struct cardstate*) ; 
 int /*<<< orphan*/  gigaset_initbcs (int /*<<< orphan*/ *,struct cardstate*,int) ; 
 int /*<<< orphan*/  gigaset_register_to_LL (struct cardstate*,char const*) ; 
 int /*<<< orphan*/  gigaset_tab_cid ; 
 int /*<<< orphan*/  gigaset_tab_nocid ; 
 int /*<<< orphan*/  init_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_valid (struct cardstate*,int /*<<< orphan*/ ) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  setup_timer (TYPE_2__*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct cardstate*) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer_tick ; 

struct cardstate *gigaset_initcs(struct gigaset_driver *drv, int channels,
				 int onechannel, int ignoreframes,
				 int cidmode, const char *modulename)
{
	struct cardstate *cs = NULL;
	unsigned long flags;
	int i;

	gig_dbg(DEBUG_INIT, "allocating cs");
	if (!(cs = alloc_cs(drv))) {
		pr_err("maximum number of devices exceeded\n");
		return NULL;
	}

	gig_dbg(DEBUG_INIT, "allocating bcs[0..%d]", channels - 1);
	cs->bcs = kmalloc(channels * sizeof(struct bc_state), GFP_KERNEL);
	if (!cs->bcs) {
		pr_err("out of memory\n");
		goto error;
	}
	gig_dbg(DEBUG_INIT, "allocating inbuf");
	cs->inbuf = kmalloc(sizeof(struct inbuf_t), GFP_KERNEL);
	if (!cs->inbuf) {
		pr_err("out of memory\n");
		goto error;
	}

	cs->cs_init = 0;
	cs->channels = channels;
	cs->onechannel = onechannel;
	cs->ignoreframes = ignoreframes;
	INIT_LIST_HEAD(&cs->temp_at_states);
	cs->running = 0;
	init_timer(&cs->timer); /* clear next & prev */
	spin_lock_init(&cs->ev_lock);
	cs->ev_tail = 0;
	cs->ev_head = 0;

	tasklet_init(&cs->event_tasklet, &gigaset_handle_event,
		     (unsigned long) cs);
	cs->commands_pending = 0;
	cs->cur_at_seq = 0;
	cs->gotfwver = -1;
	cs->open_count = 0;
	cs->dev = NULL;
	cs->tty = NULL;
	cs->tty_dev = NULL;
	cs->cidmode = cidmode != 0;
	cs->tabnocid = gigaset_tab_nocid;
	cs->tabcid = gigaset_tab_cid;

	init_waitqueue_head(&cs->waitqueue);
	cs->waiting = 0;

	cs->mode = M_UNKNOWN;
	cs->mstate = MS_UNINITIALIZED;

	for (i = 0; i < channels; ++i) {
		gig_dbg(DEBUG_INIT, "setting up bcs[%d].read", i);
		if (!gigaset_initbcs(cs->bcs + i, cs, i)) {
			pr_err("could not allocate channel %d data\n", i);
			goto error;
		}
	}

	++cs->cs_init;

	gig_dbg(DEBUG_INIT, "setting up at_state");
	spin_lock_init(&cs->lock);
	gigaset_at_init(&cs->at_state, NULL, cs, 0);
	cs->dle = 0;
	cs->cbytes = 0;

	gig_dbg(DEBUG_INIT, "setting up inbuf");
	if (onechannel) {			//FIXME distinction necessary?
		gigaset_inbuf_init(cs->inbuf, cs->bcs, cs, INS_command);
	} else
		gigaset_inbuf_init(cs->inbuf, NULL,    cs, INS_command);

	cs->connected = 0;
	cs->isdn_up = 0;

	gig_dbg(DEBUG_INIT, "setting up cmdbuf");
	cs->cmdbuf = cs->lastcmdbuf = NULL;
	spin_lock_init(&cs->cmdlock);
	cs->curlen = 0;
	cs->cmdbytes = 0;

	gig_dbg(DEBUG_INIT, "setting up iif");
	if (!gigaset_register_to_LL(cs, modulename)) {
		pr_err("error registering ISDN device\n");
		goto error;
	}

	make_valid(cs, VALID_ID);
	++cs->cs_init;
	gig_dbg(DEBUG_INIT, "setting up hw");
	if (!cs->ops->initcshw(cs))
		goto error;

	++cs->cs_init;

	/* set up character device */
	gigaset_if_init(cs);

	/* set up device sysfs */
	gigaset_init_dev_sysfs(cs);

	spin_lock_irqsave(&cs->lock, flags);
	cs->running = 1;
	spin_unlock_irqrestore(&cs->lock, flags);
	setup_timer(&cs->timer, timer_tick, (unsigned long) cs);
	cs->timer.expires = jiffies + msecs_to_jiffies(GIG_TICK);
	/* FIXME: can jiffies increase too much until the timer is added?
	 * Same problem(?) with mod_timer() in timer_tick(). */
	add_timer(&cs->timer);

	gig_dbg(DEBUG_INIT, "cs initialized");
	return cs;

error:
	gig_dbg(DEBUG_INIT, "failed");
	gigaset_freecs(cs);
	return NULL;
}