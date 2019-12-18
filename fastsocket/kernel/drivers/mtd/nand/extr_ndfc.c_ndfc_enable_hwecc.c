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
typedef  int /*<<< orphan*/  uint32_t ;
struct ndfc_controller {scalar_t__ ndfcbase; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ NDFC_CCR ; 
 int /*<<< orphan*/  NDFC_CCR_RESET_ECC ; 
 int /*<<< orphan*/  in_be32 (scalar_t__) ; 
 struct ndfc_controller ndfc_ctrl ; 
 int /*<<< orphan*/  out_be32 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void ndfc_enable_hwecc(struct mtd_info *mtd, int mode)
{
	uint32_t ccr;
	struct ndfc_controller *ndfc = &ndfc_ctrl;

	ccr = in_be32(ndfc->ndfcbase + NDFC_CCR);
	ccr |= NDFC_CCR_RESET_ECC;
	out_be32(ndfc->ndfcbase + NDFC_CCR, ccr);
	wmb();
}