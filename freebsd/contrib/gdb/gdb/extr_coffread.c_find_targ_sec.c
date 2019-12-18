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
struct find_targ_sec_arg {scalar_t__ targ_index; TYPE_1__** resultp; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_3__ {scalar_t__ target_index; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */

__attribute__((used)) static void
find_targ_sec (bfd *abfd, asection *sect, void *obj)
{
  struct find_targ_sec_arg *args = (struct find_targ_sec_arg *) obj;
  if (sect->target_index == args->targ_index)
    *args->resultp = sect;
}