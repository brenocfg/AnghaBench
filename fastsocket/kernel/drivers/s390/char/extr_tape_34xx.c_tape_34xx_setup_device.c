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
struct tape_device {struct list_head* discdata; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_EVENT (int,char*) ; 
 int /*<<< orphan*/  DBF_LH (int,char*,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 struct list_head* kmalloc (int,int /*<<< orphan*/ ) ; 
 int tape_34xx_medium_sense (struct tape_device*) ; 
 int tape_std_assign (struct tape_device*) ; 

__attribute__((used)) static int
tape_34xx_setup_device(struct tape_device * device)
{
	int			rc;
	struct list_head *	discdata;

	DBF_EVENT(6, "34xx device setup\n");
	if ((rc = tape_std_assign(device)) == 0) {
		if ((rc = tape_34xx_medium_sense(device)) != 0) {
			DBF_LH(3, "34xx medium sense returned %d\n", rc);
		}
	}
	discdata = kmalloc(sizeof(struct list_head), GFP_KERNEL);
	if (discdata) {
			INIT_LIST_HEAD(discdata);
			device->discdata = discdata;
	}

	return rc;
}