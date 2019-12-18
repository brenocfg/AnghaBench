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
struct vm_area_struct {int dummy; } ;
struct gru_vma_data {int /*<<< orphan*/  vd_lock; int /*<<< orphan*/  vd_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gru_dbg (int /*<<< orphan*/ ,char*,struct gru_vma_data*) ; 
 int /*<<< orphan*/  grudev ; 
 struct gru_vma_data* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdata_alloc ; 

struct gru_vma_data *gru_alloc_vma_data(struct vm_area_struct *vma, int tsid)
{
	struct gru_vma_data *vdata = NULL;

	vdata = kmalloc(sizeof(*vdata), GFP_KERNEL);
	if (!vdata)
		return NULL;

	STAT(vdata_alloc);
	INIT_LIST_HEAD(&vdata->vd_head);
	spin_lock_init(&vdata->vd_lock);
	gru_dbg(grudev, "alloc vdata %p\n", vdata);
	return vdata;
}