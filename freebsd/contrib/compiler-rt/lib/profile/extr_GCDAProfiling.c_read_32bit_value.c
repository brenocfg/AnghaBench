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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 size_t cur_pos ; 
 scalar_t__ new_file ; 
 int /*<<< orphan*/ * write_buffer ; 

__attribute__((used)) static uint32_t read_32bit_value() {
  uint32_t val;

  if (new_file)
    return (uint32_t)-1;

  val = *(uint32_t*)&write_buffer[cur_pos];
  cur_pos += 4;
  return val;
}