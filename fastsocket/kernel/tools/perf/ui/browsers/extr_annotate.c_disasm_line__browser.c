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
struct disasm_line {int dummy; } ;
struct browser_disasm_line {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct browser_disasm_line *disasm_line__browser(struct disasm_line *dl)
{
	return (struct browser_disasm_line *)(dl + 1);
}