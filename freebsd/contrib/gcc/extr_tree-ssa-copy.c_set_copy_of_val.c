#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct TYPE_2__ {scalar_t__ value; scalar_t__ mem_ref; } ;

/* Variables and functions */
 unsigned int SSA_NAME_VERSION (scalar_t__) ; 
 scalar_t__* cached_last_copy_of ; 
 TYPE_1__* copy_of ; 
 scalar_t__ get_last_copy_of (scalar_t__) ; 

__attribute__((used)) static inline bool
set_copy_of_val (tree dest, tree first, tree mem_ref)
{
  unsigned int dest_ver = SSA_NAME_VERSION (dest);
  tree old_first, old_last, new_last;
  
  /* Set FIRST to be the first link in COPY_OF[DEST].  If that
     changed, return true.  */
  old_first = copy_of[dest_ver].value;
  copy_of[dest_ver].value = first;
  copy_of[dest_ver].mem_ref = mem_ref;

  if (old_first != first)
    return true;

  /* If FIRST and OLD_FIRST are the same, we need to check whether the
     copy-of chain starting at FIRST ends in a different variable.  If
     the copy-of chain starting at FIRST ends up in a different
     variable than the last cached value we had for DEST, then return
     true because DEST is now a copy of a different variable.

     This test is necessary because even though the first link in the
     copy-of chain may not have changed, if any of the variables in
     the copy-of chain changed its final value, DEST will now be the
     copy of a different variable, so we have to do another round of
     propagation for everything that depends on DEST.  */
  old_last = cached_last_copy_of[dest_ver];
  new_last = get_last_copy_of (dest);
  cached_last_copy_of[dest_ver] = new_last;

  return (old_last != new_last);
}