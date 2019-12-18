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
struct ath5k_rx_status {int rs_status; int rs_phyerr; scalar_t__ rs_keyix; int rs_more; scalar_t__ rs_datalen; } ;
struct TYPE_2__ {int /*<<< orphan*/  rxerr_jumbo; int /*<<< orphan*/  rxerr_mic; int /*<<< orphan*/  rxerr_decrypt; int /*<<< orphan*/ * rxerr_phy_code; int /*<<< orphan*/  rxerr_phy; int /*<<< orphan*/  rxerr_fifo; int /*<<< orphan*/  rxerr_crc; int /*<<< orphan*/  rx_bytes_count; int /*<<< orphan*/  rx_all_count; } ;
struct ath5k_hw {TYPE_1__ stats; } ;

/* Variables and functions */
 int AR5K_RXERR_CRC ; 
 int AR5K_RXERR_DECRYPT ; 
 int AR5K_RXERR_FIFO ; 
 int AR5K_RXERR_MIC ; 
 int AR5K_RXERR_PHY ; 
 scalar_t__ AR5K_RXKEYIX_INVALID ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool
ath5k_receive_frame_ok(struct ath5k_hw *ah, struct ath5k_rx_status *rs)
{
	ah->stats.rx_all_count++;
	ah->stats.rx_bytes_count += rs->rs_datalen;

	if (unlikely(rs->rs_status)) {
		if (rs->rs_status & AR5K_RXERR_CRC)
			ah->stats.rxerr_crc++;
		if (rs->rs_status & AR5K_RXERR_FIFO)
			ah->stats.rxerr_fifo++;
		if (rs->rs_status & AR5K_RXERR_PHY) {
			ah->stats.rxerr_phy++;
			if (rs->rs_phyerr > 0 && rs->rs_phyerr < 32)
				ah->stats.rxerr_phy_code[rs->rs_phyerr]++;
			return false;
		}
		if (rs->rs_status & AR5K_RXERR_DECRYPT) {
			/*
			 * Decrypt error.  If the error occurred
			 * because there was no hardware key, then
			 * let the frame through so the upper layers
			 * can process it.  This is necessary for 5210
			 * parts which have no way to setup a ``clear''
			 * key cache entry.
			 *
			 * XXX do key cache faulting
			 */
			ah->stats.rxerr_decrypt++;
			if (rs->rs_keyix == AR5K_RXKEYIX_INVALID &&
			    !(rs->rs_status & AR5K_RXERR_CRC))
				return true;
		}
		if (rs->rs_status & AR5K_RXERR_MIC) {
			ah->stats.rxerr_mic++;
			return true;
		}

		/* reject any frames with non-crypto errors */
		if (rs->rs_status & ~(AR5K_RXERR_DECRYPT))
			return false;
	}

	if (unlikely(rs->rs_more)) {
		ah->stats.rxerr_jumbo++;
		return false;
	}
	return true;
}