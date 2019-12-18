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
struct ccw1 {int /*<<< orphan*/  cmd_code; scalar_t__ cda; scalar_t__ count; scalar_t__ flags; } ;
typedef  scalar_t__ addr_t ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */

__attribute__((used)) static inline struct ccw1 *
tape_ccw_cmd(struct ccw1 *ccw, __u8 cmd_code)
{
	ccw->cmd_code = cmd_code;
	ccw->flags = 0;
	ccw->count = 0;
	ccw->cda = (__u32)(addr_t) &ccw->cmd_code;
	return ccw + 1;
}