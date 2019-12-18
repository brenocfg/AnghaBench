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
struct irb {int dummy; } ;
struct claw_privbk {struct chbk* channel; } ;
struct chbk {int flag; int /*<<< orphan*/ * irb; int /*<<< orphan*/  devno; int /*<<< orphan*/  id; struct ccw_device* cdev; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;
struct ccw_dev_id {int /*<<< orphan*/  devno; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLAW_DBF_TEXT_ (int,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  CLAW_ID_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ccw_device_get_id (struct ccw_device*,struct ccw_dev_id*) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int
add_channel(struct ccw_device *cdev,int i,struct claw_privbk *privptr)
{
	struct chbk *p_ch;
	struct ccw_dev_id dev_id;

	CLAW_DBF_TEXT_(2, setup, "%s", dev_name(&cdev->dev));
	privptr->channel[i].flag  = i+1;   /* Read is 1 Write is 2 */
	p_ch = &privptr->channel[i];
	p_ch->cdev = cdev;
	snprintf(p_ch->id, CLAW_ID_SIZE, "cl-%s", dev_name(&cdev->dev));
	ccw_device_get_id(cdev, &dev_id);
	p_ch->devno = dev_id.devno;
	if ((p_ch->irb = kzalloc(sizeof (struct irb),GFP_KERNEL)) == NULL) {
		return -ENOMEM;
	}
	return 0;
}