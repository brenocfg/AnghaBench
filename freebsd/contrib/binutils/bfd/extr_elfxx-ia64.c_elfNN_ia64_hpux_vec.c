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
typedef  int /*<<< orphan*/  bfd_target ;
typedef  int bfd_boolean ;

/* Variables and functions */

__attribute__((used)) static bfd_boolean
elfNN_ia64_hpux_vec (const bfd_target *vec)
{
  extern const bfd_target bfd_elfNN_ia64_hpux_big_vec;
  return (vec == & bfd_elfNN_ia64_hpux_big_vec);
}