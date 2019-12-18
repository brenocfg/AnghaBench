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
struct function_info {int hi; int /*<<< orphan*/  sec; } ;
typedef  void* bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ is_nop (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static bfd_boolean
insns_at_end (struct function_info *fun, bfd_vma limit)
{
  bfd_vma off = (fun->hi + 3) & -4;

  while (off < limit && is_nop (fun->sec, off))
    off += 4;
  if (off < limit)
    {
      fun->hi = off;
      return TRUE;
    }
  fun->hi = limit;
  return FALSE;
}