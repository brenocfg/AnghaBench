#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/ * release; } ;
struct i2o_controller {int unit; char* name; int /*<<< orphan*/  context_list; int /*<<< orphan*/  context_list_counter; int /*<<< orphan*/  context_list_lock; TYPE_1__ device; int /*<<< orphan*/  lct_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  devices; int /*<<< orphan*/  in_msg; } ;
typedef  int /*<<< orphan*/  poolname ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct i2o_controller* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2O_INBOUND_MSG_FRAME_SIZE ; 
 int /*<<< orphan*/  I2O_MSG_INPOOL_MIN ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  i2o_iop_release ; 
 scalar_t__ i2o_pool_alloc (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct i2o_controller*) ; 
 struct i2o_controller* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osm_err (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

struct i2o_controller *i2o_iop_alloc(void)
{
	static int unit = 0;	/* 0 and 1 are NULL IOP and Local Host */
	struct i2o_controller *c;
	char poolname[32];

	c = kzalloc(sizeof(*c), GFP_KERNEL);
	if (!c) {
		osm_err("i2o: Insufficient memory to allocate a I2O controller."
			"\n");
		return ERR_PTR(-ENOMEM);
	}

	c->unit = unit++;
	sprintf(c->name, "iop%d", c->unit);

	snprintf(poolname, sizeof(poolname), "i2o_%s_msg_inpool", c->name);
	if (i2o_pool_alloc
	    (&c->in_msg, poolname, I2O_INBOUND_MSG_FRAME_SIZE * 4 + sizeof(u32),
	     I2O_MSG_INPOOL_MIN)) {
		kfree(c);
		return ERR_PTR(-ENOMEM);
	};

	INIT_LIST_HEAD(&c->devices);
	spin_lock_init(&c->lock);
	mutex_init(&c->lct_lock);

	device_initialize(&c->device);

	c->device.release = &i2o_iop_release;

	dev_set_name(&c->device, "iop%d", c->unit);

#if BITS_PER_LONG == 64
	spin_lock_init(&c->context_list_lock);
	atomic_set(&c->context_list_counter, 0);
	INIT_LIST_HEAD(&c->context_list);
#endif

	return c;
}