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
typedef  int u_char ;
struct nand_chip {int /*<<< orphan*/  IO_ADDR_R; } ;
struct mtd_info {struct nand_chip* priv; } ;

/* Variables and functions */
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_char cmx270_read_byte(struct mtd_info *mtd)
{
	struct nand_chip *this = mtd->priv;

	return (readl(this->IO_ADDR_R) >> 16);
}