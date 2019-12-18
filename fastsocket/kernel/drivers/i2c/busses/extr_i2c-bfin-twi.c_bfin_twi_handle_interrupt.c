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
struct bfin_twi_iface {int writeNum; int* transPtr; scalar_t__ cur_mode; int manual_stop; int cur_msg; int msg_num; int readNum; int result; int /*<<< orphan*/  complete; TYPE_1__* pmsg; int /*<<< orphan*/  read_write; } ;
struct TYPE_2__ {int flags; int* buf; int len; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 unsigned short ANAK ; 
 unsigned short BUFRDERR ; 
 int EIO ; 
 int I2C_M_RD ; 
 int /*<<< orphan*/  I2C_SMBUS_READ ; 
 int /*<<< orphan*/  I2C_SMBUS_WRITE ; 
 unsigned short MCOMP ; 
 int MDIR ; 
 unsigned short MERR ; 
 unsigned short RCVSERV ; 
 int RSTART ; 
 int /*<<< orphan*/  SSYNC () ; 
 int STOP ; 
 scalar_t__ TWI_I2C_MODE_COMBINED ; 
 scalar_t__ TWI_I2C_MODE_REPEAT ; 
 scalar_t__ TWI_I2C_MODE_STANDARDSUB ; 
 unsigned short XMTSERV ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 unsigned short read_INT_STAT (struct bfin_twi_iface*) ; 
 int read_MASTER_CTL (struct bfin_twi_iface*) ; 
 unsigned short read_MASTER_STAT (struct bfin_twi_iface*) ; 
 int read_RCV_DATA8 (struct bfin_twi_iface*) ; 
 int /*<<< orphan*/  write_INT_MASK (struct bfin_twi_iface*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_INT_STAT (struct bfin_twi_iface*,unsigned short) ; 
 int /*<<< orphan*/  write_MASTER_ADDR (struct bfin_twi_iface*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_MASTER_CTL (struct bfin_twi_iface*,int) ; 
 int /*<<< orphan*/  write_MASTER_STAT (struct bfin_twi_iface*,int) ; 
 int /*<<< orphan*/  write_XMT_DATA8 (struct bfin_twi_iface*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bfin_twi_handle_interrupt(struct bfin_twi_iface *iface)
{
	unsigned short twi_int_status = read_INT_STAT(iface);
	unsigned short mast_stat = read_MASTER_STAT(iface);

	if (twi_int_status & XMTSERV) {
		/* Transmit next data */
		if (iface->writeNum > 0) {
			write_XMT_DATA8(iface, *(iface->transPtr++));
			iface->writeNum--;
		}
		/* start receive immediately after complete sending in
		 * combine mode.
		 */
		else if (iface->cur_mode == TWI_I2C_MODE_COMBINED)
			write_MASTER_CTL(iface,
				read_MASTER_CTL(iface) | MDIR | RSTART);
		else if (iface->manual_stop)
			write_MASTER_CTL(iface,
				read_MASTER_CTL(iface) | STOP);
		else if (iface->cur_mode == TWI_I2C_MODE_REPEAT &&
		         iface->cur_msg + 1 < iface->msg_num) {
			if (iface->pmsg[iface->cur_msg + 1].flags & I2C_M_RD)
				write_MASTER_CTL(iface,
					read_MASTER_CTL(iface) | RSTART | MDIR);
			else
				write_MASTER_CTL(iface,
					(read_MASTER_CTL(iface) | RSTART) & ~MDIR);
		}
		SSYNC();
		/* Clear status */
		write_INT_STAT(iface, XMTSERV);
		SSYNC();
	}
	if (twi_int_status & RCVSERV) {
		if (iface->readNum > 0) {
			/* Receive next data */
			*(iface->transPtr) = read_RCV_DATA8(iface);
			if (iface->cur_mode == TWI_I2C_MODE_COMBINED) {
				/* Change combine mode into sub mode after
				 * read first data.
				 */
				iface->cur_mode = TWI_I2C_MODE_STANDARDSUB;
				/* Get read number from first byte in block
				 * combine mode.
				 */
				if (iface->readNum == 1 && iface->manual_stop)
					iface->readNum = *iface->transPtr + 1;
			}
			iface->transPtr++;
			iface->readNum--;
		} else if (iface->manual_stop) {
			write_MASTER_CTL(iface,
				read_MASTER_CTL(iface) | STOP);
			SSYNC();
		} else if (iface->cur_mode == TWI_I2C_MODE_REPEAT &&
		           iface->cur_msg + 1 < iface->msg_num) {
			if (iface->pmsg[iface->cur_msg + 1].flags & I2C_M_RD)
				write_MASTER_CTL(iface,
					read_MASTER_CTL(iface) | RSTART | MDIR);
			else
				write_MASTER_CTL(iface,
					(read_MASTER_CTL(iface) | RSTART) & ~MDIR);
			SSYNC();
		}
		/* Clear interrupt source */
		write_INT_STAT(iface, RCVSERV);
		SSYNC();
	}
	if (twi_int_status & MERR) {
		write_INT_STAT(iface, MERR);
		write_INT_MASK(iface, 0);
		write_MASTER_STAT(iface, 0x3e);
		write_MASTER_CTL(iface, 0);
		SSYNC();
		iface->result = -EIO;
		/* if both err and complete int stats are set, return proper
		 * results.
		 */
		if (twi_int_status & MCOMP) {
			write_INT_STAT(iface, MCOMP);
			write_INT_MASK(iface, 0);
			write_MASTER_CTL(iface, 0);
			SSYNC();
			/* If it is a quick transfer, only address bug no data,
			 * not an err, return 1.
			 */
			if (iface->writeNum == 0 && (mast_stat & BUFRDERR))
				iface->result = 1;
			/* If address not acknowledged return -1,
			 * else return 0.
			 */
			else if (!(mast_stat & ANAK))
				iface->result = 0;
		}
		complete(&iface->complete);
		return;
	}
	if (twi_int_status & MCOMP) {
		write_INT_STAT(iface, MCOMP);
		SSYNC();
		if (iface->cur_mode == TWI_I2C_MODE_COMBINED) {
			if (iface->readNum == 0) {
				/* set the read number to 1 and ask for manual
				 * stop in block combine mode
				 */
				iface->readNum = 1;
				iface->manual_stop = 1;
				write_MASTER_CTL(iface,
					read_MASTER_CTL(iface) | (0xff << 6));
			} else {
				/* set the readd number in other
				 * combine mode.
				 */
				write_MASTER_CTL(iface,
					(read_MASTER_CTL(iface) &
					(~(0xff << 6))) |
					(iface->readNum << 6));
			}
			/* remove restart bit and enable master receive */
			write_MASTER_CTL(iface,
				read_MASTER_CTL(iface) & ~RSTART);
			SSYNC();
		} else if (iface->cur_mode == TWI_I2C_MODE_REPEAT &&
				iface->cur_msg+1 < iface->msg_num) {
			iface->cur_msg++;
			iface->transPtr = iface->pmsg[iface->cur_msg].buf;
			iface->writeNum = iface->readNum =
				iface->pmsg[iface->cur_msg].len;
			/* Set Transmit device address */
			write_MASTER_ADDR(iface,
				iface->pmsg[iface->cur_msg].addr);
			if (iface->pmsg[iface->cur_msg].flags & I2C_M_RD)
				iface->read_write = I2C_SMBUS_READ;
			else {
				iface->read_write = I2C_SMBUS_WRITE;
				/* Transmit first data */
				if (iface->writeNum > 0) {
					write_XMT_DATA8(iface,
						*(iface->transPtr++));
					iface->writeNum--;
					SSYNC();
				}
			}

			if (iface->pmsg[iface->cur_msg].len <= 255)
					write_MASTER_CTL(iface,
					(read_MASTER_CTL(iface) &
					(~(0xff << 6))) |
				(iface->pmsg[iface->cur_msg].len << 6));
			else {
				write_MASTER_CTL(iface,
					(read_MASTER_CTL(iface) |
					(0xff << 6)));
				iface->manual_stop = 1;
			}
			/* remove restart bit and enable master receive */
			write_MASTER_CTL(iface,
				read_MASTER_CTL(iface) & ~RSTART);
			SSYNC();
		} else {
			iface->result = 1;
			write_INT_MASK(iface, 0);
			write_MASTER_CTL(iface, 0);
			SSYNC();
			complete(&iface->complete);
		}
	}
}