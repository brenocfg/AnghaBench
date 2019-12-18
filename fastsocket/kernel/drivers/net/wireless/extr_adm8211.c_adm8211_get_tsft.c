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
typedef  int u64 ;
typedef  int u32 ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct adm8211_priv* priv; } ;
struct adm8211_priv {int dummy; } ;

/* Variables and functions */
 int ADM8211_CSR_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSFTH ; 
 int /*<<< orphan*/  TSFTL ; 

__attribute__((used)) static u64 adm8211_get_tsft(struct ieee80211_hw *dev,
			    struct ieee80211_vif *vif)
{
	struct adm8211_priv *priv = dev->priv;
	u32 tsftl;
	u64 tsft;

	tsftl = ADM8211_CSR_READ(TSFTL);
	tsft = ADM8211_CSR_READ(TSFTH);
	tsft <<= 32;
	tsft |= tsftl;

	return tsft;
}