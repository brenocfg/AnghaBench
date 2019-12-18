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
struct overlay {unsigned int pos_increment; int size; scalar_t__ pos; } ;

/* Variables and functions */

__attribute__((used)) static void task_overlay_image_done(struct overlay *overlay)
{
   overlay->pos           = 0;
   /* Divide iteration steps by half of total descs if size is even,
    * otherwise default to 8 (arbitrary value for now to speed things up). */
   overlay->pos_increment = (overlay->size / 2) ? ((unsigned)(overlay->size / 2)) : 8;
}