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
struct re_registers {int dummy; } ;
struct re_pattern_buffer {int dummy; } ;

/* Variables and functions */
 int re_search_2 (struct re_pattern_buffer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int,int,int,struct re_registers*,int) ; 

int
re_search (struct re_pattern_buffer *bufp, const char *string, int size,
           int startpos, int range, struct re_registers *regs)
{
  return re_search_2 (bufp, NULL, 0, string, size, startpos, range,
		      regs, size);
}