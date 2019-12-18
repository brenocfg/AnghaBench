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
struct sdricoh_host {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  R21C_STATUS ; 
 int /*<<< orphan*/  R230_DATA ; 
 int /*<<< orphan*/  STATUS_READY_TO_READ ; 
 int /*<<< orphan*/  STATUS_READY_TO_WRITE ; 
 int /*<<< orphan*/  TRANSFER_TIMEOUT ; 
 int min (int,int) ; 
 scalar_t__ sdricoh_query_status (struct sdricoh_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sdricoh_readl (struct sdricoh_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdricoh_writel (struct sdricoh_host*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sdricoh_blockio(struct sdricoh_host *host, int read,
				u8 *buf, int len)
{
	int size;
	u32 data = 0;
	/* wait until the data is available */
	if (read) {
		if (sdricoh_query_status(host, STATUS_READY_TO_READ,
						TRANSFER_TIMEOUT))
			return -ETIMEDOUT;
		sdricoh_writel(host, R21C_STATUS, 0x18);
		/* read data */
		while (len) {
			data = sdricoh_readl(host, R230_DATA);
			size = min(len, 4);
			len -= size;
			while (size) {
				*buf = data & 0xFF;
				buf++;
				data >>= 8;
				size--;
			}
		}
	} else {
		if (sdricoh_query_status(host, STATUS_READY_TO_WRITE,
						TRANSFER_TIMEOUT))
			return -ETIMEDOUT;
		sdricoh_writel(host, R21C_STATUS, 0x18);
		/* write data */
		while (len) {
			size = min(len, 4);
			len -= size;
			while (size) {
				data >>= 8;
				data |= (u32)*buf << 24;
				buf++;
				size--;
			}
			sdricoh_writel(host, R230_DATA, data);
		}
	}

	if (len)
		return -EIO;

	return 0;
}