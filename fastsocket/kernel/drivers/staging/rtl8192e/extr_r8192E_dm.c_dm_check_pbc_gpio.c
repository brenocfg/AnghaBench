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
struct r8192_priv {int bpbc_pressed; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int BIT0 ; 
 int BIT6 ; 
 int /*<<< orphan*/  COMP_IO ; 
 int /*<<< orphan*/  GPI ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int read_nic_byte (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static	void	dm_check_pbc_gpio(struct net_device *dev)
{
#ifdef RTL8192U
	struct r8192_priv *priv = ieee80211_priv(dev);
	u8 tmp1byte;


	tmp1byte = read_nic_byte(dev,GPI);
	if(tmp1byte == 0xff)
	return;

	if (tmp1byte&BIT6 || tmp1byte&BIT0)
	{
		// Here we only set bPbcPressed to TRUE
		// After trigger PBC, the variable will be set to FALSE
		RT_TRACE(COMP_IO, "CheckPbcGPIO - PBC is pressed\n");
		priv->bpbc_pressed = true;
	}
#endif

}