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
struct macro_buffer {char* text; int len; int shared; int last_token; scalar_t__ size; } ;

/* Variables and functions */

__attribute__((used)) static void
init_shared_buffer (struct macro_buffer *buf, char *addr, int len)
{
  buf->text = addr;
  buf->len = len;
  buf->shared = 1;
  buf->size = 0;
  buf->last_token = -1;
}