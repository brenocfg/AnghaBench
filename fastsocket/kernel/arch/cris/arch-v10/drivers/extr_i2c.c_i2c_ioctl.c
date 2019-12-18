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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ ETRAXI2C_IOCTYPE ; 
 int /*<<< orphan*/  I2C_ARGREG (unsigned long) ; 
 int /*<<< orphan*/  I2C_ARGSLAVE (unsigned long) ; 
 int /*<<< orphan*/  I2C_ARGVALUE (unsigned long) ; 
#define  I2C_READREG 129 
#define  I2C_WRITEREG 128 
 int _IOC_NR (unsigned int) ; 
 scalar_t__ _IOC_TYPE (unsigned int) ; 
 unsigned char i2c_readreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_writereg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,unsigned char,...) ; 

__attribute__((used)) static int
i2c_ioctl(struct inode *inode, struct file *file,
	  unsigned int cmd, unsigned long arg)
{
	if(_IOC_TYPE(cmd) != ETRAXI2C_IOCTYPE) {
		return -EINVAL;
	}

	switch (_IOC_NR(cmd)) {
		case I2C_WRITEREG:
			/* write to an i2c slave */
			D(printk("i2cw %d %d %d\n", 
				 I2C_ARGSLAVE(arg),
				 I2C_ARGREG(arg),
				 I2C_ARGVALUE(arg)));

			return i2c_writereg(I2C_ARGSLAVE(arg),
					    I2C_ARGREG(arg),
					    I2C_ARGVALUE(arg));
		case I2C_READREG:
		{
			unsigned char val;
			/* read from an i2c slave */
			D(printk("i2cr %d %d ", 
				I2C_ARGSLAVE(arg),
				I2C_ARGREG(arg)));
			val = i2c_readreg(I2C_ARGSLAVE(arg), I2C_ARGREG(arg));
			D(printk("= %d\n", val));
			return val;
		}					    
		default:
			return -EINVAL;

	}
	
	return 0;
}