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
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

bfd_boolean
_bfd_mips_elf_ignore_discarded_relocs (asection *sec)
{
  if (strcmp (sec->name, ".pdr") == 0)
    return TRUE;
  return FALSE;
}