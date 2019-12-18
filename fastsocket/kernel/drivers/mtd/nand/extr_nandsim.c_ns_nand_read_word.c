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
typedef  int uint16_t ;
struct nand_chip {int (* read_byte ) (struct mtd_info*) ;} ;
struct mtd_info {scalar_t__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  NS_DBG (char*) ; 
 int stub1 (struct mtd_info*) ; 
 int stub2 (struct mtd_info*) ; 

__attribute__((used)) static uint16_t ns_nand_read_word(struct mtd_info *mtd)
{
	struct nand_chip *chip = (struct nand_chip *)mtd->priv;

	NS_DBG("read_word\n");

	return chip->read_byte(mtd) | (chip->read_byte(mtd) << 8);
}