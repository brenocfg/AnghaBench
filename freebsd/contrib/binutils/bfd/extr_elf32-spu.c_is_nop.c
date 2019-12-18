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
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_4__ {scalar_t__ size; int /*<<< orphan*/  owner; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bfd_get_section_contents (int /*<<< orphan*/ ,TYPE_1__*,unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bfd_boolean
is_nop (asection *sec, bfd_vma off)
{
  unsigned char insn[4];

  if (off + 4 > sec->size
      || !bfd_get_section_contents (sec->owner, sec, insn, off, 4))
    return FALSE;
  if ((insn[0] & 0xbf) == 0 && (insn[1] & 0xe0) == 0x20)
    return TRUE;
  if (insn[0] == 0 && insn[1] == 0 && insn[2] == 0 && insn[3] == 0)
    return TRUE;
  return FALSE;
}