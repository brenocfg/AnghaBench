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
typedef  int /*<<< orphan*/  u16 ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_PHY_HT_C1_CLIP1THRES ; 
 int /*<<< orphan*/  B43_PHY_HT_C2_CLIP1THRES ; 
 int /*<<< orphan*/  B43_PHY_HT_C3_CLIP1THRES ; 
 int /*<<< orphan*/  b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b43_phy_ht_read_clip_detection(struct b43_wldev *dev, u16 *clip_st)
{
	clip_st[0] = b43_phy_read(dev, B43_PHY_HT_C1_CLIP1THRES);
	clip_st[1] = b43_phy_read(dev, B43_PHY_HT_C2_CLIP1THRES);
	clip_st[2] = b43_phy_read(dev, B43_PHY_HT_C3_CLIP1THRES);
}