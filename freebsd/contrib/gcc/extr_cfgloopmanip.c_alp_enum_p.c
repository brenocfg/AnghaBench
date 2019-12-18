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
typedef  scalar_t__ basic_block ;

/* Variables and functions */

__attribute__((used)) static bool
alp_enum_p (basic_block bb, void *alp_header)
{
  return bb != (basic_block) alp_header;
}