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

/* Variables and functions */
 int /*<<< orphan*/  INSN_ADDRESSES_FREE () ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ insn_lengths ; 
 scalar_t__ insn_lengths_max_uid ; 
 scalar_t__ uid_align ; 
 scalar_t__ uid_shuid ; 

void
init_insn_lengths (void)
{
  if (uid_shuid)
    {
      free (uid_shuid);
      uid_shuid = 0;
    }
  if (insn_lengths)
    {
      free (insn_lengths);
      insn_lengths = 0;
      insn_lengths_max_uid = 0;
    }
#ifdef HAVE_ATTR_length
  INSN_ADDRESSES_FREE ();
#endif
  if (uid_align)
    {
      free (uid_align);
      uid_align = 0;
    }
}