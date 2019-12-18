#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct raw3215_info {char* inbuf; int /*<<< orphan*/  tlet; int /*<<< orphan*/  empty_wait; int /*<<< orphan*/ * buffer; struct ccw_device* cdev; } ;
struct ccw_device {int /*<<< orphan*/  handler; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int NR_3215 ; 
 scalar_t__ RAW3215_BUFFER_SIZE ; 
 scalar_t__ RAW3215_INBUF_SIZE ; 
 struct raw3215_info* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct raw3215_info*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct raw3215_info*) ; 
 void* kmalloc (scalar_t__,int) ; 
 int /*<<< orphan*/  memset (struct raw3215_info*,int /*<<< orphan*/ ,int) ; 
 struct raw3215_info** raw3215 ; 
 int /*<<< orphan*/  raw3215_device_lock ; 
 int /*<<< orphan*/  raw3215_irq ; 
 int /*<<< orphan*/  raw3215_wakeup ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int raw3215_probe (struct ccw_device *cdev)
{
	struct raw3215_info *raw;
	int line;

	/* Console is special. */
	if (raw3215[0] && (raw3215[0] == dev_get_drvdata(&cdev->dev)))
		return 0;
	raw = kmalloc(sizeof(struct raw3215_info) +
		      RAW3215_INBUF_SIZE, GFP_KERNEL|GFP_DMA);
	if (raw == NULL)
		return -ENOMEM;

	spin_lock(&raw3215_device_lock);
	for (line = 0; line < NR_3215; line++) {
		if (!raw3215[line]) {
			raw3215[line] = raw;
			break;
		}
	}
	spin_unlock(&raw3215_device_lock);
	if (line == NR_3215) {
		kfree(raw);
		return -ENODEV;
	}

	raw->cdev = cdev;
	raw->inbuf = (char *) raw + sizeof(struct raw3215_info);
	memset(raw, 0, sizeof(struct raw3215_info));
	raw->buffer = kmalloc(RAW3215_BUFFER_SIZE,
				       GFP_KERNEL|GFP_DMA);
	if (raw->buffer == NULL) {
		spin_lock(&raw3215_device_lock);
		raw3215[line] = NULL;
		spin_unlock(&raw3215_device_lock);
		kfree(raw);
		return -ENOMEM;
	}
	init_waitqueue_head(&raw->empty_wait);
	tasklet_init(&raw->tlet, raw3215_wakeup, (unsigned long) raw);

	dev_set_drvdata(&cdev->dev, raw);
	cdev->handler = raw3215_irq;

	return 0;
}