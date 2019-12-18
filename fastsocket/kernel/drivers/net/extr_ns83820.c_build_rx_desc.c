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
struct ns83820 {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int DESC_BUFPTR ; 
 size_t DESC_CMDSTS ; 
 size_t DESC_EXTSTS ; 
 int DESC_LINK ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  desc_addr_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static inline void build_rx_desc(struct ns83820 *dev, __le32 *desc, dma_addr_t link, dma_addr_t buf, u32 cmdsts, u32 extsts)
{
	desc_addr_set(desc + DESC_LINK, link);
	desc_addr_set(desc + DESC_BUFPTR, buf);
	desc[DESC_EXTSTS] = cpu_to_le32(extsts);
	mb();
	desc[DESC_CMDSTS] = cpu_to_le32(cmdsts);
}