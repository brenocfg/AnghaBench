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
typedef  int /*<<< orphan*/  u8 ;
struct efx_spi_device {int dummy; } ;
struct efx_nic {int dummy; } ;
typedef  size_t loff_t ;

/* Variables and functions */
 int EINTR ; 
 int EIO ; 
 int FALCON_SPI_MAX_LEN ; 
 int /*<<< orphan*/  SPI_READ ; 
 unsigned int SPI_WREN ; 
 int /*<<< orphan*/  SPI_WRITE ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  current ; 
 unsigned int efx_spi_munge_command (struct efx_spi_device const*,int /*<<< orphan*/ ,size_t) ; 
 int falcon_spi_cmd (struct efx_nic*,struct efx_spi_device const*,unsigned int,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,size_t) ; 
 int falcon_spi_wait_write (struct efx_nic*,struct efx_spi_device const*) ; 
 int /*<<< orphan*/  falcon_spi_write_limit (struct efx_spi_device const*,size_t) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 size_t min (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 

int
falcon_spi_write(struct efx_nic *efx, const struct efx_spi_device *spi,
		 loff_t start, size_t len, size_t *retlen, const u8 *buffer)
{
	u8 verify_buffer[FALCON_SPI_MAX_LEN];
	size_t block_len, pos = 0;
	unsigned int command;
	int rc = 0;

	while (pos < len) {
		rc = falcon_spi_cmd(efx, spi, SPI_WREN, -1, NULL, NULL, 0);
		if (rc)
			break;

		block_len = min(len - pos,
				falcon_spi_write_limit(spi, start + pos));
		command = efx_spi_munge_command(spi, SPI_WRITE, start + pos);
		rc = falcon_spi_cmd(efx, spi, command, start + pos,
				    buffer + pos, NULL, block_len);
		if (rc)
			break;

		rc = falcon_spi_wait_write(efx, spi);
		if (rc)
			break;

		command = efx_spi_munge_command(spi, SPI_READ, start + pos);
		rc = falcon_spi_cmd(efx, spi, command, start + pos,
				    NULL, verify_buffer, block_len);
		if (memcmp(verify_buffer, buffer + pos, block_len)) {
			rc = -EIO;
			break;
		}

		pos += block_len;

		/* Avoid locking up the system */
		cond_resched();
		if (signal_pending(current)) {
			rc = -EINTR;
			break;
		}
	}

	if (retlen)
		*retlen = pos;
	return rc;
}