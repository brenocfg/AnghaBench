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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct r8192_priv {TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct ieee80211_network {size_t rates_len; int* rates; size_t rates_ex_len; int* rates_ex; } ;
struct TYPE_2__ {struct ieee80211_network current_network; } ;

/* Variables and functions */
#define  MGN_11M 139 
#define  MGN_12M 138 
#define  MGN_18M 137 
#define  MGN_1M 136 
#define  MGN_24M 135 
#define  MGN_2M 134 
#define  MGN_36M 133 
#define  MGN_48M 132 
#define  MGN_54M 131 
#define  MGN_5_5M 130 
#define  MGN_6M 129 
#define  MGN_9M 128 
 int /*<<< orphan*/  RRSR_11M ; 
 int /*<<< orphan*/  RRSR_12M ; 
 int /*<<< orphan*/  RRSR_18M ; 
 int /*<<< orphan*/  RRSR_1M ; 
 int /*<<< orphan*/  RRSR_24M ; 
 int /*<<< orphan*/  RRSR_2M ; 
 int /*<<< orphan*/  RRSR_36M ; 
 int /*<<< orphan*/  RRSR_48M ; 
 int /*<<< orphan*/  RRSR_54M ; 
 int /*<<< orphan*/  RRSR_5_5M ; 
 int /*<<< orphan*/  RRSR_6M ; 
 int /*<<< orphan*/  RRSR_9M ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 

__attribute__((used)) static void rtl8192_config_rate(struct net_device* dev, u16* rate_config)
{
	 struct r8192_priv *priv = ieee80211_priv(dev);
	 struct ieee80211_network *net;
	 u8 i=0, basic_rate = 0;
	 net = & priv->ieee80211->current_network;

	 for (i=0; i<net->rates_len; i++)
	 {
		 basic_rate = net->rates[i]&0x7f;
		 switch(basic_rate)
		 {
			 case MGN_1M:	*rate_config |= RRSR_1M;	break;
			 case MGN_2M:	*rate_config |= RRSR_2M;	break;
			 case MGN_5_5M:	*rate_config |= RRSR_5_5M;	break;
			 case MGN_11M:	*rate_config |= RRSR_11M;	break;
			 case MGN_6M:	*rate_config |= RRSR_6M;	break;
			 case MGN_9M:	*rate_config |= RRSR_9M;	break;
			 case MGN_12M:	*rate_config |= RRSR_12M;	break;
			 case MGN_18M:	*rate_config |= RRSR_18M;	break;
			 case MGN_24M:	*rate_config |= RRSR_24M;	break;
			 case MGN_36M:	*rate_config |= RRSR_36M;	break;
			 case MGN_48M:	*rate_config |= RRSR_48M;	break;
			 case MGN_54M:	*rate_config |= RRSR_54M;	break;
		 }
	 }
	 for (i=0; i<net->rates_ex_len; i++)
	 {
		 basic_rate = net->rates_ex[i]&0x7f;
		 switch(basic_rate)
		 {
			 case MGN_1M:	*rate_config |= RRSR_1M;	break;
			 case MGN_2M:	*rate_config |= RRSR_2M;	break;
			 case MGN_5_5M:	*rate_config |= RRSR_5_5M;	break;
			 case MGN_11M:	*rate_config |= RRSR_11M;	break;
			 case MGN_6M:	*rate_config |= RRSR_6M;	break;
			 case MGN_9M:	*rate_config |= RRSR_9M;	break;
			 case MGN_12M:	*rate_config |= RRSR_12M;	break;
			 case MGN_18M:	*rate_config |= RRSR_18M;	break;
			 case MGN_24M:	*rate_config |= RRSR_24M;	break;
			 case MGN_36M:	*rate_config |= RRSR_36M;	break;
			 case MGN_48M:	*rate_config |= RRSR_48M;	break;
			 case MGN_54M:	*rate_config |= RRSR_54M;	break;
		 }
	 }
}