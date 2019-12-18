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
struct fb_info {int /*<<< orphan*/  mm_lock; int /*<<< orphan*/  fix; int /*<<< orphan*/  var; scalar_t__ par; } ;
struct atafb_par {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* encode_fix ) (int /*<<< orphan*/ *,struct atafb_par*) ;int /*<<< orphan*/  (* decode_var ) (int /*<<< orphan*/ *,struct atafb_par*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ata_set_par (struct atafb_par*) ; 
 TYPE_1__* fbhw ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct atafb_par*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,struct atafb_par*) ; 

__attribute__((used)) static int atafb_set_par(struct fb_info *info)
{
	struct atafb_par *par = (struct atafb_par *)info->par;

	/* Decode wanted screen parameters */
	fbhw->decode_var(&info->var, par);
	mutex_lock(&info->mm_lock);
	fbhw->encode_fix(&info->fix, par);
	mutex_unlock(&info->mm_lock);

	/* Set new videomode */
	ata_set_par(par);

	return 0;
}