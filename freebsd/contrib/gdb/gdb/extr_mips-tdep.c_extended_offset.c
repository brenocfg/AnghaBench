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
typedef  int CORE_ADDR ;

/* Variables and functions */

__attribute__((used)) static CORE_ADDR
extended_offset (unsigned int extension)
{
  CORE_ADDR value;
  value = (extension >> 21) & 0x3f;	/* * extract 15:11 */
  value = value << 6;
  value |= (extension >> 16) & 0x1f;	/* extrace 10:5 */
  value = value << 5;
  value |= extension & 0x01f;	/* extract 4:0 */
  return value;
}