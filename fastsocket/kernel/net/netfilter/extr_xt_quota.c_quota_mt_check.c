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
struct xt_quota_info {int flags; int /*<<< orphan*/  quota; TYPE_1__* master; } ;
struct xt_mtchk_param {struct xt_quota_info* matchinfo; } ;
struct TYPE_2__ {int /*<<< orphan*/  quota; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int XT_QUOTA_MASK ; 
 TYPE_1__* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool quota_mt_check(const struct xt_mtchk_param *par)
{
	struct xt_quota_info *q = par->matchinfo;

	if (q->flags & ~XT_QUOTA_MASK)
		return false;

	q->master = kmalloc(sizeof(*q->master), GFP_KERNEL);
	if (q->master == NULL)
		return false;

	q->master->quota = q->quota;
	return true;
}