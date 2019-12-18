#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ offset; } ;
struct TYPE_4__ {TYPE_1__ target; } ;
struct disasm_line {TYPE_2__ ops; } ;

/* Variables and functions */
 scalar_t__ UINT64_MAX ; 

__attribute__((used)) static inline bool disasm_line__has_offset(const struct disasm_line *dl)
{
	return dl->ops.target.offset != UINT64_MAX;
}