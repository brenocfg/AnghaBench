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
typedef  int /*<<< orphan*/  u8 ;
struct efx_spi_device {size_t erase_size; scalar_t__ erase_command; } ;
struct efx_nic {int dummy; } ;
struct TYPE_2__ {struct efx_mtd* priv; } ;
struct efx_mtd_partition {TYPE_1__ mtd; } ;
struct efx_mtd {struct efx_nic* efx; struct efx_spi_device* spi; } ;
typedef  unsigned int loff_t ;
typedef  int /*<<< orphan*/  empty ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int EFX_SPI_VERIFY_BUF_LEN ; 
 int EINTR ; 
 int EINVAL ; 
 int EIO ; 
 int EOPNOTSUPP ; 
 scalar_t__ SPI_WREN ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  current ; 
 int efx_spi_slow_wait (struct efx_mtd_partition*,int) ; 
 int efx_spi_unlock (struct efx_nic*,struct efx_spi_device const*) ; 
 int falcon_spi_cmd (struct efx_nic*,struct efx_spi_device const*,scalar_t__,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int falcon_spi_read (struct efx_nic*,struct efx_spi_device const*,unsigned int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 unsigned int min (size_t,int) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
efx_spi_erase(struct efx_mtd_partition *part, loff_t start, size_t len)
{
	struct efx_mtd *efx_mtd = part->mtd.priv;
	const struct efx_spi_device *spi = efx_mtd->spi;
	struct efx_nic *efx = efx_mtd->efx;
	unsigned pos, block_len;
	u8 empty[EFX_SPI_VERIFY_BUF_LEN];
	u8 buffer[EFX_SPI_VERIFY_BUF_LEN];
	int rc;

	if (len != spi->erase_size)
		return -EINVAL;

	if (spi->erase_command == 0)
		return -EOPNOTSUPP;

	rc = efx_spi_unlock(efx, spi);
	if (rc)
		return rc;
	rc = falcon_spi_cmd(efx, spi, SPI_WREN, -1, NULL, NULL, 0);
	if (rc)
		return rc;
	rc = falcon_spi_cmd(efx, spi, spi->erase_command, start, NULL,
			    NULL, 0);
	if (rc)
		return rc;
	rc = efx_spi_slow_wait(part, false);

	/* Verify the entire region has been wiped */
	memset(empty, 0xff, sizeof(empty));
	for (pos = 0; pos < len; pos += block_len) {
		block_len = min(len - pos, sizeof(buffer));
		rc = falcon_spi_read(efx, spi, start + pos, block_len,
				     NULL, buffer);
		if (rc)
			return rc;
		if (memcmp(empty, buffer, block_len))
			return -EIO;

		/* Avoid locking up the system */
		cond_resched();
		if (signal_pending(current))
			return -EINTR;
	}

	return rc;
}