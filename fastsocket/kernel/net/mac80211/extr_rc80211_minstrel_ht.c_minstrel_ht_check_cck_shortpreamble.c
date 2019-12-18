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
typedef  int u8 ;
struct minstrel_priv {int dummy; } ;
struct minstrel_ht_sta {int cck_supported_short; TYPE_1__* groups; } ;
struct TYPE_2__ {int supported; } ;

/* Variables and functions */
 size_t MINSTREL_CCK_GROUP ; 

__attribute__((used)) static void
minstrel_ht_check_cck_shortpreamble(struct minstrel_priv *mp,
				    struct minstrel_ht_sta *mi, bool val)
{
	u8 supported = mi->groups[MINSTREL_CCK_GROUP].supported;

	if (!supported || !mi->cck_supported_short)
		return;

	if (supported & (mi->cck_supported_short << (val * 4)))
		return;

	supported ^= mi->cck_supported_short | (mi->cck_supported_short << 4);
	mi->groups[MINSTREL_CCK_GROUP].supported = supported;
}