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
struct display {int /*<<< orphan*/  num_text; int /*<<< orphan*/ * text_ptr; int /*<<< orphan*/  ip; int /*<<< orphan*/  write_pp; } ;

/* Variables and functions */
 int /*<<< orphan*/  png_set_text (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
text_restore(struct display *dp)
{
   /* libpng makes a copy, so this is fine: */
   if (dp->text_ptr != NULL)
      png_set_text(dp->write_pp, dp->ip, dp->text_ptr, dp->num_text);
}