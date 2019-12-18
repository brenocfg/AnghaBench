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
typedef  scalar_t__ u64 ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ EHCA_INVAL_ADDR ; 

__attribute__((used)) static int ehca_dma_mapping_error(struct ib_device *dev, u64 dma_addr)
{
	return dma_addr == EHCA_INVAL_ADDR;
}