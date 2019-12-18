#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* program; char const* file; int /*<<< orphan*/  test; scalar_t__ warning_count; scalar_t__ error_count; int /*<<< orphan*/ * end_ptr; int /*<<< orphan*/  info_ptr; int /*<<< orphan*/ * png_ptr; } ;
typedef  TYPE_1__ display ;

/* Variables and functions */
 int /*<<< orphan*/  init ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
init_display(display *d, const char *program)
{
   memset(d, 0, sizeof *d);
   d->png_ptr = NULL;
   d->info_ptr = d->end_ptr = NULL;
   d->error_count = d->warning_count = 0;
   d->program = program;
   d->file = program;
   d->test = init;
}