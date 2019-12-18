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
typedef  int /*<<< orphan*/  u_char ;
struct tmio_nand {scalar_t__ fcr; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ FCR_DATA ; 
 struct tmio_nand* mtd_to_tmio (struct mtd_info*) ; 
 int /*<<< orphan*/  tmio_ioread16_rep (scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void tmio_nand_read_buf(struct mtd_info *mtd, u_char *buf, int len)
{
	struct tmio_nand *tmio = mtd_to_tmio(mtd);

	tmio_ioread16_rep(tmio->fcr + FCR_DATA, buf, len >> 1);
}