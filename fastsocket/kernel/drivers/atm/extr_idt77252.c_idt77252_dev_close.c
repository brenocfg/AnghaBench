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
typedef  int u32 ;
struct idt77252_dev {int /*<<< orphan*/  name; } ;
struct atm_dev {struct idt77252_dev* dev_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIPRINTK (char*,int /*<<< orphan*/ ) ; 
 int SAR_CFG_FBIE ; 
 int SAR_CFG_RAWIE ; 
 int SAR_CFG_RQFIE ; 
 int SAR_CFG_RXPTH ; 
 int SAR_CFG_TMOIE ; 
 int SAR_CFG_TXEN ; 
 int SAR_CFG_TXINT ; 
 int SAR_CFG_TXSFI ; 
 int SAR_CFG_TXUIE ; 
 int /*<<< orphan*/  SAR_REG_CFG ; 
 int SAR_RX_DELAY ; 
 int /*<<< orphan*/  close_card_oam (struct idt77252_dev*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void idt77252_dev_close(struct atm_dev *dev)
{
	struct idt77252_dev *card = dev->dev_data;
	u32 conf;

	close_card_oam(card);

	conf = SAR_CFG_RXPTH |	/* enable receive path           */
	    SAR_RX_DELAY |	/* interrupt on complete PDU     */
	    SAR_CFG_RAWIE |	/* interrupt enable on raw cells */
	    SAR_CFG_RQFIE |	/* interrupt on RSQ almost full  */
	    SAR_CFG_TMOIE |	/* interrupt on timer overflow   */
	    SAR_CFG_FBIE |	/* interrupt on low free buffers */
	    SAR_CFG_TXEN |	/* transmit operation enable     */
	    SAR_CFG_TXINT |	/* interrupt on transmit status  */
	    SAR_CFG_TXUIE |	/* interrupt on xmit underrun    */
	    SAR_CFG_TXSFI	/* interrupt on TSQ almost full  */
	    ;

	writel(readl(SAR_REG_CFG) & ~(conf), SAR_REG_CFG);

	DIPRINTK("%s: closed IDT77252 ABR SAR.\n", card->name);
}