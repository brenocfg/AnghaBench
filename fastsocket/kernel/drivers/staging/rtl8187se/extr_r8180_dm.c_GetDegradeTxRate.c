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
GetDegradeTxRate(
        struct net_device *dev,
        u8         rate
        )
{
        struct r8180_priv *priv = ieee80211_priv(dev);
        u8                      DownRate;

        // Upgrade 1 degree.
        switch(rate)
        {
        case 108: // Down to 48Mbps.
                DownRate = 96;
                break;

        case 96: // Down to 36Mbps.
                DownRate = 72;
                break;

        case 72: // Down to 24Mbps.
                DownRate = 48;
                break;

        case 48: // Down to 18Mbps.
                DownRate = 36;
                break;

        case 36: // Down to 11Mbps.
                DownRate = 22;
                break;

        case 22: // Down to 5.5Mbps.
                DownRate = 11;
                break;

        case 11: // Down to 2Mbps.
                DownRate = 4;
                break;

        case 4: // Down to 1Mbps.
                DownRate = 2;
                break;

        case 2: // Down to 1Mbps.
                DownRate = 2;
                break;

        default:
                printk("GetDegradeTxRate(): Input Tx Rate(%d) is undefined!\n", rate);
                return rate;
        }
        // Check if the rate is valid.
        if(IncludedInSupportedRates(priv, DownRate))
        {
//              printk("GetDegradeTxRate(): GetDegrade Tx rate(%d) from %d!\n", DownRate, priv->CurrentOperaRate);
                return DownRate;
        }
        else
        {
                //printk("GetDegradeTxRate(): Tx rate (%d) is not in supported rates\n", DownRate);
                return rate;
        }
        return rate;
}