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
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ bfd_get_32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  the_bfd ; 

__attribute__((used)) static int
compare_pdr_entries (const void *a, const void *b)
{
  CORE_ADDR lhs = bfd_get_32 (the_bfd, (bfd_byte *) a);
  CORE_ADDR rhs = bfd_get_32 (the_bfd, (bfd_byte *) b);

  if (lhs < rhs)
    return -1;
  else if (lhs == rhs)
    return 0;
  else
    return 1;
}