#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int /*<<< orphan*/  iv32; int /*<<< orphan*/  iv16; } ;
struct TYPE_6__ {TYPE_1__ tx; int /*<<< orphan*/  txlock; } ;
struct TYPE_7__ {TYPE_2__ tkip; } ;
struct TYPE_8__ {int keyidx; } ;
struct ieee80211_key {TYPE_3__ u; TYPE_4__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_unaligned_le32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * write_tkip_iv (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

u8 *ieee80211_tkip_add_iv(u8 *pos, struct ieee80211_key *key)
{
	lockdep_assert_held(&key->u.tkip.txlock);

	pos = write_tkip_iv(pos, key->u.tkip.tx.iv16);
	*pos++ = (key->conf.keyidx << 6) | (1 << 5) /* Ext IV */;
	put_unaligned_le32(key->u.tkip.tx.iv32, pos);
	return pos + 4;
}