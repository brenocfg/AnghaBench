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
typedef  int u8 ;
struct r8180_priv {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IncludedInSupportedRates (struct r8180_priv*,int) ; 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int) ; 

u8
GetUpgradeTxRate(
        struct net_device *dev,
        u8                              rate
        )
{
        struct r8180_priv *priv = ieee80211_priv(dev);
        u8                      UpRate;

        // Upgrade 1 degree.
        switch(rate)
        {
        case 108: // Up to 54Mbps.
                UpRate = 108;
                break;

        case 96: // Up to 54Mbps.
                UpRate = 108;
                break;

        case 72: // Up to 48Mbps.
                UpRate = 96;
                break;

        case 48: // Up to 36Mbps.
                UpRate = 72;
                break;

        case 36: // Up to 24Mbps.
                UpRate = 48;
                break;

        case 22: // Up to 18Mbps.
                UpRate = 36;
                break;

        case 11: // Up to 11Mbps.
                UpRate = 22;
                break;

        case 4: // Up to 5.5Mbps.
                UpRate = 11;
                break;

        case 2: // Up to 2Mbps.
                UpRate = 4;
                break;

        default:
                printk("GetUpgradeTxRate(): Input Tx Rate(%d) is undefined!\n", rate);
                return rate;
        }
        // Check if the rate is valid.
        if(IncludedInSupportedRates(priv, UpRate))
        {
//              printk("GetUpgradeTxRate(): GetUpgrade Tx rate(%d) from %d !\n", UpRate, priv->CurrentOperaRate);
                return UpRate;
        }
        else
        {
                //printk("GetUpgradeTxRate(): Tx rate (%d) is not in supported rates\n", UpRate);
                return rate;
        }
        return rate;
}