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
typedef  int u32 ;
struct rtl_fw_phy_action {size_t size; int /*<<< orphan*/ * code; } ;
struct rtl8169_private {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
#define  PHY_BJMPN 143 
#define  PHY_CLEAR_READCOUNT 142 
#define  PHY_COMP_EQ_SKIPN 141 
#define  PHY_COMP_NEQ_SKIPN 140 
#define  PHY_DATA_AND 139 
#define  PHY_DATA_OR 138 
#define  PHY_DELAY_MS 137 
#define  PHY_READ 136 
#define  PHY_READCOUNT_EQ_SKIP 135 
#define  PHY_READ_EFUSE 134 
#define  PHY_READ_MAC_BYTE 133 
#define  PHY_SKIPN 132 
#define  PHY_WRITE 131 
#define  PHY_WRITE_ERI_WORD 130 
#define  PHY_WRITE_MAC_BYTE 129 
#define  PHY_WRITE_PREVIOUS 128 
 int /*<<< orphan*/  ifup ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_err (struct rtl8169_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static bool rtl_fw_data_ok(struct rtl8169_private *tp, struct net_device *dev,
			   struct rtl_fw_phy_action *pa)
{
	bool rc = false;
	size_t index;

	for (index = 0; index < pa->size; index++) {
		u32 action = le32_to_cpu(pa->code[index]);
		u32 regno = (action & 0x0fff0000) >> 16;

		switch(action & 0xf0000000) {
		case PHY_READ:
		case PHY_DATA_OR:
		case PHY_DATA_AND:
		case PHY_READ_EFUSE:
		case PHY_CLEAR_READCOUNT:
		case PHY_WRITE:
		case PHY_WRITE_PREVIOUS:
		case PHY_DELAY_MS:
			break;

		case PHY_BJMPN:
			if (regno > index) {
				netif_err(tp, ifup, tp->dev,
					  "Out of range of firmware\n");
				goto out;
			}
			break;
		case PHY_READCOUNT_EQ_SKIP:
			if (index + 2 >= pa->size) {
				netif_err(tp, ifup, tp->dev,
					  "Out of range of firmware\n");
				goto out;
			}
			break;
		case PHY_COMP_EQ_SKIPN:
		case PHY_COMP_NEQ_SKIPN:
		case PHY_SKIPN:
			if (index + 1 + regno >= pa->size) {
				netif_err(tp, ifup, tp->dev,
					  "Out of range of firmware\n");
				goto out;
			}
			break;

		case PHY_READ_MAC_BYTE:
		case PHY_WRITE_MAC_BYTE:
		case PHY_WRITE_ERI_WORD:
		default:
			netif_err(tp, ifup, tp->dev,
				  "Invalid action 0x%08x\n", action);
			goto out;
		}
	}
	rc = true;
out:
	return rc;
}