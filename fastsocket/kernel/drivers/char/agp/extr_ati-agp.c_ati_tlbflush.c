#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct agp_memory {int dummy; } ;
struct TYPE_2__ {scalar_t__ registers; } ;

/* Variables and functions */
 scalar_t__ ATI_GART_CACHE_CNTRL ; 
 TYPE_1__ ati_generic_private ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void ati_tlbflush(struct agp_memory * mem)
{
	writel(1, ati_generic_private.registers+ATI_GART_CACHE_CNTRL);
	readl(ati_generic_private.registers+ATI_GART_CACHE_CNTRL);	/* PCI Posting. */
}