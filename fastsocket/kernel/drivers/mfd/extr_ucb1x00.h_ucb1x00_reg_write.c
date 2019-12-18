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
struct ucb1x00 {int /*<<< orphan*/  mcp; } ;

/* Variables and functions */
 int /*<<< orphan*/  mcp_reg_write (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static inline void ucb1x00_reg_write(struct ucb1x00 *ucb, unsigned int reg, unsigned int val)
{
	mcp_reg_write(ucb->mcp, reg, val);
}