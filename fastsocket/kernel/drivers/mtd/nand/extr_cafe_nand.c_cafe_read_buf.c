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
typedef  int /*<<< orphan*/  uint8_t ;
struct mtd_info {struct cafe_priv* priv; } ;
struct cafe_priv {scalar_t__ datalen; TYPE_1__* pdev; scalar_t__ mmio; scalar_t__ dmabuf; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CAFE_NAND_READ_DATA ; 
 int /*<<< orphan*/  cafe_dev_dbg (int /*<<< orphan*/ *,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  memcpy_fromio (int /*<<< orphan*/ *,scalar_t__,int) ; 
 scalar_t__ usedma ; 

__attribute__((used)) static void cafe_read_buf(struct mtd_info *mtd, uint8_t *buf, int len)
{
	struct cafe_priv *cafe = mtd->priv;

	if (usedma)
		memcpy(buf, cafe->dmabuf + cafe->datalen, len);
	else
		memcpy_fromio(buf, cafe->mmio + CAFE_NAND_READ_DATA + cafe->datalen, len);

	cafe_dev_dbg(&cafe->pdev->dev, "Copy 0x%x bytes from position 0x%x in read buffer.\n",
		  len, cafe->datalen);
	cafe->datalen += len;
}