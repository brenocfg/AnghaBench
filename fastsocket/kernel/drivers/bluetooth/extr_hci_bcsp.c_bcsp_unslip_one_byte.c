#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char u8 ;
struct bcsp_struct {int rx_esc_state; int /*<<< orphan*/  rx_count; int /*<<< orphan*/  rx_state; TYPE_1__* rx_skb; int /*<<< orphan*/  message_crc; } ;
struct TYPE_3__ {int* data; } ;

/* Variables and functions */
#define  BCSP_ESCSTATE_ESC 129 
#define  BCSP_ESCSTATE_NOESC 128 
 int /*<<< orphan*/  BCSP_W4_CRC ; 
 int /*<<< orphan*/  BCSP_W4_PKT_DELIMITER ; 
 int /*<<< orphan*/  BT_ERR (char*,unsigned char) ; 
 int /*<<< orphan*/  bcsp_crc_update (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree_skb (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,int) ; 
 int /*<<< orphan*/  skb_put (TYPE_1__*,int) ; 

__attribute__((used)) static inline void bcsp_unslip_one_byte(struct bcsp_struct *bcsp, unsigned char byte)
{
	const u8 c0 = 0xc0, db = 0xdb;

	switch (bcsp->rx_esc_state) {
	case BCSP_ESCSTATE_NOESC:
		switch (byte) {
		case 0xdb:
			bcsp->rx_esc_state = BCSP_ESCSTATE_ESC;
			break;
		default:
			memcpy(skb_put(bcsp->rx_skb, 1), &byte, 1);
			if ((bcsp->rx_skb-> data[0] & 0x40) != 0 && 
					bcsp->rx_state != BCSP_W4_CRC)
				bcsp_crc_update(&bcsp->message_crc, byte);
			bcsp->rx_count--;
		}
		break;

	case BCSP_ESCSTATE_ESC:
		switch (byte) {
		case 0xdc:
			memcpy(skb_put(bcsp->rx_skb, 1), &c0, 1);
			if ((bcsp->rx_skb-> data[0] & 0x40) != 0 && 
					bcsp->rx_state != BCSP_W4_CRC)
				bcsp_crc_update(&bcsp-> message_crc, 0xc0);
			bcsp->rx_esc_state = BCSP_ESCSTATE_NOESC;
			bcsp->rx_count--;
			break;

		case 0xdd:
			memcpy(skb_put(bcsp->rx_skb, 1), &db, 1);
			if ((bcsp->rx_skb-> data[0] & 0x40) != 0 && 
					bcsp->rx_state != BCSP_W4_CRC) 
				bcsp_crc_update(&bcsp-> message_crc, 0xdb);
			bcsp->rx_esc_state = BCSP_ESCSTATE_NOESC;
			bcsp->rx_count--;
			break;

		default:
			BT_ERR ("Invalid byte %02x after esc byte", byte);
			kfree_skb(bcsp->rx_skb);
			bcsp->rx_skb = NULL;
			bcsp->rx_state = BCSP_W4_PKT_DELIMITER;
			bcsp->rx_count = 0;
		}
	}
}