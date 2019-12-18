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
typedef  int /*<<< orphan*/  u32 ;
struct s3cmci_host {scalar_t__ sdiimsk; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline u32 enable_imask(struct s3cmci_host *host, u32 imask)
{
	u32 newmask;

	newmask = readl(host->base + host->sdiimsk);
	newmask |= imask;

	writel(newmask, host->base + host->sdiimsk);

	return newmask;
}