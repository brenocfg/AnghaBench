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
struct TYPE_2__ {int /*<<< orphan*/  ext_ptr; } ;
struct sti_struct {int /*<<< orphan*/  lock; int /*<<< orphan*/  glob_cfg; TYPE_1__ outptr; int /*<<< orphan*/  inq_conf; int /*<<< orphan*/  outptr_ext; } ;
struct sti_conf_inptr {int /*<<< orphan*/  member_0; } ;
typedef  int s32 ;

/* Variables and functions */
 int STI_CALL (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sti_conf_inptr*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STI_PTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  default_conf_flags ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sti_inq_conf(struct sti_struct *sti)
{
	struct sti_conf_inptr inptr = { 0, };
	unsigned long flags;
	s32 ret;

	sti->outptr.ext_ptr = STI_PTR(&sti->outptr_ext);
	
	do {
		spin_lock_irqsave(&sti->lock, flags);
		ret = STI_CALL(sti->inq_conf, &default_conf_flags,
			&inptr, &sti->outptr, sti->glob_cfg);
		spin_unlock_irqrestore(&sti->lock, flags);
	} while (ret == 1);
}