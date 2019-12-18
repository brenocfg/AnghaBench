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
typedef  int u32 ;
typedef  int u16 ;
struct zd_chip {int /*<<< orphan*/  mutex; } ;
struct aw_pt_bi {int dummy; } ;

/* Variables and functions */
 int BCN_MODE_AP ; 
 int BCN_MODE_IBSS ; 
 int /*<<< orphan*/  CR_BCN_INTERVAL ; 
#define  NL80211_IFTYPE_ADHOC 130 
#define  NL80211_IFTYPE_AP 129 
#define  NL80211_IFTYPE_MESH_POINT 128 
 int /*<<< orphan*/  ZD_ASSERT (int /*<<< orphan*/ ) ; 
 int get_aw_pt_bi (struct zd_chip*,struct aw_pt_bi*) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int set_aw_pt_bi (struct zd_chip*,struct aw_pt_bi*) ; 
 int zd_iowrite32_locked (struct zd_chip*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_beacon_interval(struct zd_chip *chip, u16 interval,
			       u8 dtim_period, int type)
{
	int r;
	struct aw_pt_bi s;
	u32 b_interval, mode_flag;

	ZD_ASSERT(mutex_is_locked(&chip->mutex));

	if (interval > 0) {
		switch (type) {
		case NL80211_IFTYPE_ADHOC:
		case NL80211_IFTYPE_MESH_POINT:
			mode_flag = BCN_MODE_IBSS;
			break;
		case NL80211_IFTYPE_AP:
			mode_flag = BCN_MODE_AP;
			break;
		default:
			mode_flag = 0;
			break;
		}
	} else {
		dtim_period = 0;
		mode_flag = 0;
	}

	b_interval = mode_flag | (dtim_period << 16) | interval;

	r = zd_iowrite32_locked(chip, b_interval, CR_BCN_INTERVAL);
	if (r)
		return r;
	r = get_aw_pt_bi(chip, &s);
	if (r)
		return r;
	return set_aw_pt_bi(chip, &s);
}