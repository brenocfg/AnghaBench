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
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ALI1535_KILL ; 
 int ALI1535_STS_BUSERR ; 
 int ALI1535_STS_BUSY ; 
 int ALI1535_STS_DEV ; 
 int ALI1535_STS_DONE ; 
 int ALI1535_STS_ERR ; 
 int ALI1535_STS_FAIL ; 
 int ALI1535_STS_IDLE ; 
 int ALI1535_T_OUT ; 
 int EBUSY ; 
 int EIO ; 
 int ENXIO ; 
 int ETIMEDOUT ; 
 int MAX_TIMEOUT ; 
 int /*<<< orphan*/  SMBHSTADD ; 
 int /*<<< orphan*/  SMBHSTCMD ; 
 int /*<<< orphan*/  SMBHSTDAT0 ; 
 int /*<<< orphan*/  SMBHSTDAT1 ; 
 int /*<<< orphan*/  SMBHSTPORT ; 
 int /*<<< orphan*/  SMBHSTSTS ; 
 int /*<<< orphan*/  SMBHSTTYP ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ali1535_transaction(struct i2c_adapter *adap)
{
	int temp;
	int result = 0;
	int timeout = 0;

	dev_dbg(&adap->dev, "Transaction (pre): STS=%02x, TYP=%02x, "
		"CMD=%02x, ADD=%02x, DAT0=%02x, DAT1=%02x\n",
		inb_p(SMBHSTSTS), inb_p(SMBHSTTYP), inb_p(SMBHSTCMD),
		inb_p(SMBHSTADD), inb_p(SMBHSTDAT0), inb_p(SMBHSTDAT1));

	/* get status */
	temp = inb_p(SMBHSTSTS);

	/* Make sure the SMBus host is ready to start transmitting */
	/* Check the busy bit first */
	if (temp & ALI1535_STS_BUSY) {
		/* If the host controller is still busy, it may have timed out
		 * in the previous transaction, resulting in a "SMBus Timeout"
		 * printk.  I've tried the following to reset a stuck busy bit.
		 *   1. Reset the controller with an KILL command. (this
		 *      doesn't seem to clear the controller if an external
		 *      device is hung)
		 *   2. Reset the controller and the other SMBus devices with a
		 *      T_OUT command. (this clears the host busy bit if an
		 *      external device is hung, but it comes back upon a new
		 *      access to a device)
		 *   3. Disable and reenable the controller in SMBHSTCFG. Worst
		 *      case, nothing seems to work except power reset.
		 */

		/* Try resetting entire SMB bus, including other devices - This
		 * may not work either - it clears the BUSY bit but then the
		 * BUSY bit may come back on when you try and use the chip
		 * again.  If that's the case you are stuck.
		 */
		dev_info(&adap->dev,
			"Resetting entire SMB Bus to clear busy condition (%02x)\n",
			temp);
		outb_p(ALI1535_T_OUT, SMBHSTTYP);
		temp = inb_p(SMBHSTSTS);
	}

	/* now check the error bits and the busy bit */
	if (temp & (ALI1535_STS_ERR | ALI1535_STS_BUSY)) {
		/* do a clear-on-write */
		outb_p(0xFF, SMBHSTSTS);
		if ((temp = inb_p(SMBHSTSTS)) &
		    (ALI1535_STS_ERR | ALI1535_STS_BUSY)) {
			/* This is probably going to be correctable only by a
			 * power reset as one of the bits now appears to be
			 * stuck */
			/* This may be a bus or device with electrical problems. */
			dev_err(&adap->dev,
				"SMBus reset failed! (0x%02x) - controller or "
				"device on bus is probably hung\n", temp);
			return -EBUSY;
		}
	} else {
		/* check and clear done bit */
		if (temp & ALI1535_STS_DONE) {
			outb_p(temp, SMBHSTSTS);
		}
	}

	/* start the transaction by writing anything to the start register */
	outb_p(0xFF, SMBHSTPORT);

	/* We will always wait for a fraction of a second! */
	timeout = 0;
	do {
		msleep(1);
		temp = inb_p(SMBHSTSTS);
	} while (((temp & ALI1535_STS_BUSY) && !(temp & ALI1535_STS_IDLE))
		 && (timeout++ < MAX_TIMEOUT));

	/* If the SMBus is still busy, we give up */
	if (timeout > MAX_TIMEOUT) {
		result = -ETIMEDOUT;
		dev_err(&adap->dev, "SMBus Timeout!\n");
	}

	if (temp & ALI1535_STS_FAIL) {
		result = -EIO;
		dev_dbg(&adap->dev, "Error: Failed bus transaction\n");
	}

	/* Unfortunately the ALI SMB controller maps "no response" and "bus
	 * collision" into a single bit. No reponse is the usual case so don't
	 * do a printk.  This means that bus collisions go unreported.
	 */
	if (temp & ALI1535_STS_BUSERR) {
		result = -ENXIO;
		dev_dbg(&adap->dev,
			"Error: no response or bus collision ADD=%02x\n",
			inb_p(SMBHSTADD));
	}

	/* haven't ever seen this */
	if (temp & ALI1535_STS_DEV) {
		result = -EIO;
		dev_err(&adap->dev, "Error: device error\n");
	}

	/* check to see if the "command complete" indication is set */
	if (!(temp & ALI1535_STS_DONE)) {
		result = -ETIMEDOUT;
		dev_err(&adap->dev, "Error: command never completed\n");
	}

	dev_dbg(&adap->dev, "Transaction (post): STS=%02x, TYP=%02x, "
		"CMD=%02x, ADD=%02x, DAT0=%02x, DAT1=%02x\n",
		inb_p(SMBHSTSTS), inb_p(SMBHSTTYP), inb_p(SMBHSTCMD),
		inb_p(SMBHSTADD), inb_p(SMBHSTDAT0), inb_p(SMBHSTDAT1));

	/* take consequent actions for error conditions */
	if (!(temp & ALI1535_STS_DONE)) {
		/* issue "kill" to reset host controller */
		outb_p(ALI1535_KILL,SMBHSTTYP);
		outb_p(0xFF,SMBHSTSTS);
	} else if (temp & ALI1535_STS_ERR) {
		/* issue "timeout" to reset all devices on bus */
		outb_p(ALI1535_T_OUT,SMBHSTTYP);
		outb_p(0xFF,SMBHSTSTS);
	}

	return result;
}