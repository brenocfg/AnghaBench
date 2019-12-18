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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  cur_pos ; 
 scalar_t__ new_file ; 
 int* write_buffer ; 

__attribute__((used)) static uint32_t read_le_32bit_value() {
  uint32_t val = 0;
  int i;

  if (new_file)
    return (uint32_t)-1;

  for (i = 0; i < 4; i++)
    val |= write_buffer[cur_pos++] << (8*i);
  return val;
}