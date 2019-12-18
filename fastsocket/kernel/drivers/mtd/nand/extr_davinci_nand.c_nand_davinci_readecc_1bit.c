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
struct mtd_info {int dummy; } ;
struct davinci_nand_info {int core_chipsel; } ;

/* Variables and functions */
 scalar_t__ NANDF1ECC_OFFSET ; 
 int /*<<< orphan*/  davinci_nand_readl (struct davinci_nand_info*,scalar_t__) ; 
 struct davinci_nand_info* to_davinci_nand (struct mtd_info*) ; 

__attribute__((used)) static inline uint32_t nand_davinci_readecc_1bit(struct mtd_info *mtd)
{
	struct davinci_nand_info *info = to_davinci_nand(mtd);

	return davinci_nand_readl(info, NANDF1ECC_OFFSET
			+ 4 * info->core_chipsel);
}