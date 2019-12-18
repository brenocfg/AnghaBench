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
struct subchannel_id {int dummy; } ;
struct subchannel {int /*<<< orphan*/  todo_work; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct subchannel* ERR_PTR (int) ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cio_validate_subchannel (struct subchannel*,struct subchannel_id) ; 
 int /*<<< orphan*/  css_sch_todo ; 
 int /*<<< orphan*/  kfree (struct subchannel*) ; 
 struct subchannel* kmalloc (int,int) ; 

__attribute__((used)) static struct subchannel *
css_alloc_subchannel(struct subchannel_id schid)
{
	struct subchannel *sch;
	int ret;

	sch = kmalloc (sizeof (*sch), GFP_KERNEL | GFP_DMA);
	if (sch == NULL)
		return ERR_PTR(-ENOMEM);
	ret = cio_validate_subchannel (sch, schid);
	if (ret < 0) {
		kfree(sch);
		return ERR_PTR(ret);
	}
	INIT_WORK(&sch->todo_work, css_sch_todo);
	return sch;
}