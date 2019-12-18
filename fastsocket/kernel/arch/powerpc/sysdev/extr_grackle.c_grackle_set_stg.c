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
struct pci_controller {int /*<<< orphan*/  cfg_data; int /*<<< orphan*/  cfg_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRACKLE_CFA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned int GRACKLE_PICR1_STG ; 
 unsigned int in_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_le32 (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void grackle_set_stg(struct pci_controller* bp, int enable)
{
	unsigned int val;

	out_be32(bp->cfg_addr, GRACKLE_CFA(0, 0, 0xa8));
	val = in_le32(bp->cfg_data);
	val = enable? (val | GRACKLE_PICR1_STG) :
		(val & ~GRACKLE_PICR1_STG);
	out_be32(bp->cfg_addr, GRACKLE_CFA(0, 0, 0xa8));
	out_le32(bp->cfg_data, val);
	(void)in_le32(bp->cfg_data);
}