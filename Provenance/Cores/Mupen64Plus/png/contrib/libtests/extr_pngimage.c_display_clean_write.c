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
struct display {int /*<<< orphan*/ * write_pp; } ;

/* Variables and functions */
 int /*<<< orphan*/  png_destroy_write_struct (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
display_clean_write(struct display *dp)
{
      if (dp->write_pp != NULL)
         png_destroy_write_struct(&dp->write_pp, NULL);
}