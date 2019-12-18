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
 size_t cur_pos ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  resize_write_buffer (size_t) ; 
 int /*<<< orphan*/ * write_buffer ; 

__attribute__((used)) static void write_bytes(const char *s, size_t len) {
  resize_write_buffer(len);
  memcpy(&write_buffer[cur_pos], s, len);
  cur_pos += len;
}