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
struct thingie {int member_1; int /*<<< orphan*/  bits; int /*<<< orphan*/  member_0; } ;
struct net_device {int dummy; } ;
struct dscc4_dev_priv {int /*<<< orphan*/  parity; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCR1 ; 
 int /*<<< orphan*/  CrcMask ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  PARITY_CRC16_PR0_CCITT ; 
 int /*<<< orphan*/  PARITY_CRC16_PR1_CCITT ; 
 int /*<<< orphan*/  PARITY_CRC32_PR0_CCITT ; 
 int /*<<< orphan*/  PARITY_CRC32_PR1_CCITT ; 
 int dscc4_match (struct thingie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scc_patchl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dscc4_dev_priv*,struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dscc4_crc_setting(struct dscc4_dev_priv *dpriv,
			     struct net_device *dev)
{
	struct thingie crc[] = {
		{ PARITY_CRC16_PR0_CCITT,	0x00000010 },
		{ PARITY_CRC16_PR1_CCITT,	0x00000000 },
		{ PARITY_CRC32_PR0_CCITT,	0x00000011 },
		{ PARITY_CRC32_PR1_CCITT,	0x00000001 }
	};
	int i, ret = 0;

	i = dscc4_match(crc, dpriv->parity);
	if (i >= 0)
		scc_patchl(CrcMask, crc[i].bits, dpriv, dev, CCR1);
	else
		ret = -EOPNOTSUPP;
	return ret;
}