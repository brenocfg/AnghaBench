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
typedef  int /*<<< orphan*/  rc_uint_type ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bfd_putb32 (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  bfd_putl32 (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ target_is_bigendian ; 

__attribute__((used)) static void
target_put_32 (void *p, rc_uint_type value)
{
  assert (!! p);

  if (target_is_bigendian)
    bfd_putb32 (value, p);
  else
    bfd_putl32 (value, p);
}