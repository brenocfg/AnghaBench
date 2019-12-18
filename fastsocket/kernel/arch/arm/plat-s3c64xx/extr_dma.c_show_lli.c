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
struct pl080s_lli {int /*<<< orphan*/  control1; int /*<<< orphan*/  control0; int /*<<< orphan*/  next_lli; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,struct pl080s_lli*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void show_lli(struct pl080s_lli *lli)
{
	pr_debug("LLI[%p] %08x->%08x, NL %08x C %08x,%08x\n",
		 lli, lli->src_addr, lli->dst_addr, lli->next_lli,
		 lli->control0, lli->control1);
}