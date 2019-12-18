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
 int FAIL ; 

__attribute__((used)) static int
validate_offset_imm (unsigned int val, int hwse)
{
  if ((hwse && val > 255) || val > 4095)
    return FAIL;
  return val;
}