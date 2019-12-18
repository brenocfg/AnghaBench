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
struct bfad_im_s {int /*<<< orphan*/ * drv_workq; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ *) ; 

void
bfad_destroy_workq(struct bfad_im_s *im)
{
	if (im && im->drv_workq) {
		flush_workqueue(im->drv_workq);
		destroy_workqueue(im->drv_workq);
		im->drv_workq = NULL;
	}
}