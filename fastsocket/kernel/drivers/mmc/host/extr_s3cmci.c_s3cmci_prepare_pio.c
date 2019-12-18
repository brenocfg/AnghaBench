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
struct s3cmci_host {int /*<<< orphan*/  pio_active; scalar_t__ pio_count; scalar_t__ pio_bytes; scalar_t__ pio_sgptr; } ;
struct mmc_data {int flags; } ;

/* Variables and functions */
 int BOTH_DIR ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int MMC_DATA_WRITE ; 
 int S3C2410_SDIIMSK_RXFIFOHALF ; 
 int S3C2410_SDIIMSK_RXFIFOLAST ; 
 int S3C2410_SDIIMSK_TXFIFOHALF ; 
 int /*<<< orphan*/  XFER_READ ; 
 int /*<<< orphan*/  XFER_WRITE ; 
 int /*<<< orphan*/  do_pio_write (struct s3cmci_host*) ; 
 int /*<<< orphan*/  enable_imask (struct s3cmci_host*,int) ; 

__attribute__((used)) static int s3cmci_prepare_pio(struct s3cmci_host *host, struct mmc_data *data)
{
	int rw = (data->flags & MMC_DATA_WRITE) ? 1 : 0;

	BUG_ON((data->flags & BOTH_DIR) == BOTH_DIR);

	host->pio_sgptr = 0;
	host->pio_bytes = 0;
	host->pio_count = 0;
	host->pio_active = rw ? XFER_WRITE : XFER_READ;

	if (rw) {
		do_pio_write(host);
		enable_imask(host, S3C2410_SDIIMSK_TXFIFOHALF);
	} else {
		enable_imask(host, S3C2410_SDIIMSK_RXFIFOHALF
			     | S3C2410_SDIIMSK_RXFIFOLAST);
	}

	return 0;
}