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
struct Scsi_Host {scalar_t__ irq; } ;

/* Variables and functions */
 int CSR_DIR_READ ; 
 int CSR_HOST_BUF_NOT_RDY ; 
 int CSR_INT_BASE ; 
 int /*<<< orphan*/  DTC_BLK_CNT ; 
 int /*<<< orphan*/  DTC_CONTROL_REG ; 
 scalar_t__ DTC_DATA_BUF ; 
 int D_CR_ACCESS ; 
 int /*<<< orphan*/  MODE_REG ; 
 int MR_DMA_MODE ; 
 int MR_ENABLE_EOP_INTR ; 
 int /*<<< orphan*/  NCR5380_local_declare () ; 
 int NCR5380_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NCR5380_setup (struct Scsi_Host*) ; 
 int /*<<< orphan*/  NCR5380_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RESET_PARITY_INTERRUPT_REG ; 
 scalar_t__ SCSI_IRQ_NONE ; 
 scalar_t__ base ; 
 int dtc_maxi ; 
 int /*<<< orphan*/  memcpy_fromio (unsigned char*,scalar_t__,int) ; 
 int /*<<< orphan*/  rtrc (int) ; 

__attribute__((used)) static inline int NCR5380_pread(struct Scsi_Host *instance, unsigned char *dst, int len)
{
	unsigned char *d = dst;
	int i;			/* For counting time spent in the poll-loop */
	NCR5380_local_declare();
	NCR5380_setup(instance);

	i = 0;
	NCR5380_read(RESET_PARITY_INTERRUPT_REG);
	NCR5380_write(MODE_REG, MR_ENABLE_EOP_INTR | MR_DMA_MODE);
	if (instance->irq == SCSI_IRQ_NONE)
		NCR5380_write(DTC_CONTROL_REG, CSR_DIR_READ);
	else
		NCR5380_write(DTC_CONTROL_REG, CSR_DIR_READ | CSR_INT_BASE);
	NCR5380_write(DTC_BLK_CNT, len >> 7);	/* Block count */
	rtrc(1);
	while (len > 0) {
		rtrc(2);
		while (NCR5380_read(DTC_CONTROL_REG) & CSR_HOST_BUF_NOT_RDY)
			++i;
		rtrc(3);
		memcpy_fromio(d, base + DTC_DATA_BUF, 128);
		d += 128;
		len -= 128;
		rtrc(7);
		/*** with int's on, it sometimes hangs after here.
		 * Looks like something makes HBNR go away. */
	}
	rtrc(4);
	while (!(NCR5380_read(DTC_CONTROL_REG) & D_CR_ACCESS))
		++i;
	NCR5380_write(MODE_REG, 0);	/* Clear the operating mode */
	rtrc(0);
	NCR5380_read(RESET_PARITY_INTERRUPT_REG);
	if (i > dtc_maxi)
		dtc_maxi = i;
	return (0);
}