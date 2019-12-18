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
struct display {int /*<<< orphan*/  original_file; int /*<<< orphan*/  written_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
display_destroy(struct display *dp)
{
    /* Release any memory held in the display. */
#  ifdef PNG_WRITE_PNG_SUPPORTED
      buffer_destroy(&dp->written_file);
#  endif

   buffer_destroy(&dp->original_file);
}