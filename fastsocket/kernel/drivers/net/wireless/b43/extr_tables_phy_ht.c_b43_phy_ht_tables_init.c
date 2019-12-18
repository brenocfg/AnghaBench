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
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B43_HTTAB16 (int,int) ; 
 int /*<<< orphan*/  B43_HTTAB32 (int,int) ; 
 scalar_t__ B43_HTTAB_1A_C0_LATE_SIZE ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  b43_httab_0x12 ; 
 int /*<<< orphan*/  b43_httab_0x1a ; 
 int /*<<< orphan*/  b43_httab_0x1a_0x140 ; 
 int /*<<< orphan*/  b43_httab_0x1a_0x1c0 ; 
 int /*<<< orphan*/  b43_httab_0x1a_0x240 ; 
 int /*<<< orphan*/  b43_httab_0x1a_0xc0 ; 
 int /*<<< orphan*/  b43_httab_0x1a_0xc0_late ; 
 int /*<<< orphan*/  b43_httab_0x1b ; 
 int /*<<< orphan*/  b43_httab_0x1b_0x140 ; 
 int /*<<< orphan*/  b43_httab_0x1b_0x1c0 ; 
 int /*<<< orphan*/  b43_httab_0x1b_0x240 ; 
 int /*<<< orphan*/  b43_httab_0x1c ; 
 int /*<<< orphan*/  b43_httab_0x1c_0x140 ; 
 int /*<<< orphan*/  b43_httab_0x1c_0x1c0 ; 
 int /*<<< orphan*/  b43_httab_0x1c_0x240 ; 
 int /*<<< orphan*/  b43_httab_0x1f ; 
 int /*<<< orphan*/  b43_httab_0x20 ; 
 int /*<<< orphan*/  b43_httab_0x21 ; 
 int /*<<< orphan*/  b43_httab_0x22 ; 
 int /*<<< orphan*/  b43_httab_0x23 ; 
 int /*<<< orphan*/  b43_httab_0x24 ; 
 int /*<<< orphan*/  b43_httab_0x25 ; 
 int /*<<< orphan*/  b43_httab_0x26 ; 
 int /*<<< orphan*/  b43_httab_0x27 ; 
 int /*<<< orphan*/  b43_httab_0x2f ; 
 int /*<<< orphan*/  httab_upload (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void b43_phy_ht_tables_init(struct b43_wldev *dev)
{
	BUILD_BUG_ON(ARRAY_SIZE(b43_httab_0x1a_0xc0_late) !=
			B43_HTTAB_1A_C0_LATE_SIZE);

	httab_upload(dev, B43_HTTAB16(0x12, 0), b43_httab_0x12);
	httab_upload(dev, B43_HTTAB16(0x27, 0), b43_httab_0x27);
	httab_upload(dev, B43_HTTAB16(0x26, 0), b43_httab_0x26);
	httab_upload(dev, B43_HTTAB32(0x25, 0), b43_httab_0x25);
	httab_upload(dev, B43_HTTAB32(0x2f, 0), b43_httab_0x2f);
	httab_upload(dev, B43_HTTAB16(0x1a, 0), b43_httab_0x1a);
	httab_upload(dev, B43_HTTAB16(0x1b, 0), b43_httab_0x1b);
	httab_upload(dev, B43_HTTAB16(0x1c, 0), b43_httab_0x1c);
	httab_upload(dev, B43_HTTAB32(0x1a, 0x0c0), b43_httab_0x1a_0xc0);
	httab_upload(dev, B43_HTTAB32(0x1a, 0x140), b43_httab_0x1a_0x140);
	httab_upload(dev, B43_HTTAB32(0x1b, 0x140), b43_httab_0x1b_0x140);
	httab_upload(dev, B43_HTTAB32(0x1c, 0x140), b43_httab_0x1c_0x140);
	httab_upload(dev, B43_HTTAB16(0x1a, 0x1c0), b43_httab_0x1a_0x1c0);
	httab_upload(dev, B43_HTTAB16(0x1b, 0x1c0), b43_httab_0x1b_0x1c0);
	httab_upload(dev, B43_HTTAB16(0x1c, 0x1c0), b43_httab_0x1c_0x1c0);
	httab_upload(dev, B43_HTTAB16(0x1a, 0x240), b43_httab_0x1a_0x240);
	httab_upload(dev, B43_HTTAB16(0x1b, 0x240), b43_httab_0x1b_0x240);
	httab_upload(dev, B43_HTTAB16(0x1c, 0x240), b43_httab_0x1c_0x240);
	httab_upload(dev, B43_HTTAB32(0x1f, 0), b43_httab_0x1f);
	httab_upload(dev, B43_HTTAB32(0x21, 0), b43_httab_0x21);
	httab_upload(dev, B43_HTTAB32(0x23, 0), b43_httab_0x23);
	httab_upload(dev, B43_HTTAB32(0x20, 0), b43_httab_0x20);
	httab_upload(dev, B43_HTTAB32(0x22, 0), b43_httab_0x22);
	httab_upload(dev, B43_HTTAB32(0x24, 0), b43_httab_0x24);
}