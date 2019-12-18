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
struct TYPE_3__ {int /*<<< orphan*/ ** gendisk; } ;
typedef  TYPE_1__ ctlr_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  put_disk (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cciss_free_gendisk(ctlr_info_t *h, int drv_index)
{
	put_disk(h->gendisk[drv_index]);
	h->gendisk[drv_index] = NULL;
}