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
typedef  int uint64_t ;

/* Variables and functions */
 int WRITE_BUFFER_SIZE ; 
 int cur_buffer_size ; 
 scalar_t__ cur_pos ; 
 int /*<<< orphan*/  new_file ; 
 int /*<<< orphan*/  realloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_buffer ; 

__attribute__((used)) static void resize_write_buffer(uint64_t size) {
  if (!new_file) return;
  size += cur_pos;
  if (size <= cur_buffer_size) return;
  size = (size - 1) / WRITE_BUFFER_SIZE + 1;
  size *= WRITE_BUFFER_SIZE;
  write_buffer = realloc(write_buffer, size);
  cur_buffer_size = size;
}