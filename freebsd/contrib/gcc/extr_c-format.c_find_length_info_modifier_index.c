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
struct TYPE_3__ {scalar_t__ name; } ;
typedef  TYPE_1__ format_length_info ;

/* Variables and functions */
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ strchr (scalar_t__,int) ; 

__attribute__((used)) static unsigned int
find_length_info_modifier_index (const format_length_info *fli, int c)
{
  unsigned i;

  for (i = 0; fli->name; i++, fli++)
    if (strchr (fli->name, c))
      return i;

  /* We shouldn't be looking for a non-existent modifier.  */
  gcc_unreachable ();
}