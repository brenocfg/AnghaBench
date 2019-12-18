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
struct meth_private {int phy_addr; int /*<<< orphan*/  meth_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 int ENODEV ; 
#define  PHY_DP83840 131 
#define  PHY_ICS1889 130 
#define  PHY_ICS1890 129 
#define  PHY_QS6612X 128 
 unsigned long mdio_read (struct meth_private*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mdio_probe(struct meth_private *priv)
{
	int i;
	unsigned long p2, p3, flags;
	/* check if phy is detected already */
	if(priv->phy_addr>=0&&priv->phy_addr<32)
		return 0;
	spin_lock_irqsave(&priv->meth_lock, flags);
	for (i=0;i<32;++i){
		priv->phy_addr=i;
		p2=mdio_read(priv,2);
		p3=mdio_read(priv,3);
#if MFE_DEBUG>=2
		switch ((p2<<12)|(p3>>4)){
		case PHY_QS6612X:
			DPRINTK("PHY is QS6612X\n");
			break;
		case PHY_ICS1889:
			DPRINTK("PHY is ICS1889\n");
			break;
		case PHY_ICS1890:
			DPRINTK("PHY is ICS1890\n");
			break;
		case PHY_DP83840:
			DPRINTK("PHY is DP83840\n");
			break;
		}
#endif
		if(p2!=0xffff&&p2!=0x0000){
			DPRINTK("PHY code: %x\n",(p2<<12)|(p3>>4));
			break;
		}
	}
	spin_unlock_irqrestore(&priv->meth_lock, flags);
	if(priv->phy_addr<32) {
		return 0;
	}
	DPRINTK("Oopsie! PHY is not known!\n");
	priv->phy_addr=-1;
	return -ENODEV;
}