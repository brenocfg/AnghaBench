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
typedef  int /*<<< orphan*/  segT ;
struct TYPE_3__ {int /*<<< orphan*/  section; } ;
typedef  TYPE_1__ asymbol ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* bfd_make_debug_symbol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdoutput ; 

__attribute__((used)) static segT
fetch_coff_debug_section (void)
{
  static segT debug_section;

  if (!debug_section)
    {
      const asymbol *s;

      s = bfd_make_debug_symbol (stdoutput, NULL, 0);
      assert (s != 0);
      debug_section = s->section;
    }
  return debug_section;
}