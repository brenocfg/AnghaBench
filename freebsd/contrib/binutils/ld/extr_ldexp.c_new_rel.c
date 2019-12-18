#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_3__ {char* str; int /*<<< orphan*/ * section; int /*<<< orphan*/  value; int /*<<< orphan*/  valid_p; } ;
struct TYPE_4__ {TYPE_1__ result; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__ expld ; 

__attribute__((used)) static void
new_rel (bfd_vma value, char *str, asection *section)
{
  expld.result.valid_p = TRUE;
  expld.result.value = value;
  expld.result.str = str;
  expld.result.section = section;
}