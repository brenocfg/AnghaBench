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
struct ieee80211_sta {int dummy; } ;
struct ath_rate_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ath_rate_priv*) ; 

__attribute__((used)) static void ath_rate_free_sta(void *priv, struct ieee80211_sta *sta,
			      void *priv_sta)
{
	struct ath_rate_priv *rate_priv = priv_sta;
	kfree(rate_priv);
}