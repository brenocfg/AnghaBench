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
 int /*<<< orphan*/  mcp_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ucb1x00_enable(struct ucb1x00 *ucb)
{
	mcp_enable(ucb->mcp);
}