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
struct ptr_loc {int /*<<< orphan*/  lineno; int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 struct ptr_loc* get_rtx_ptr_loc (void const*) ; 
 int /*<<< orphan*/  set_rtx_ptr_loc (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
copy_rtx_ptr_loc (const void *new_ptr, const void *old_ptr)
{
  const struct ptr_loc *loc = get_rtx_ptr_loc (old_ptr);
  if (loc != 0)
    set_rtx_ptr_loc (new_ptr, loc->filename, loc->lineno);
}