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
typedef  int u64 ;
typedef  int u32 ;
struct cpu_private {int /*<<< orphan*/  reg; int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  wrmsr_safe_on_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int write_msr(struct cpu_private *priv, u64 val)
{
	u32 low, high;

	high = (val >> 32) & 0xffffffff;
	low = val & 0xffffffff;

	if (!wrmsr_safe_on_cpu(priv->cpu, priv->reg, low, high))
		return 0;

	return -EPERM;
}