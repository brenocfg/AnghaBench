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
union i2c_smbus_data {int byte; int word; int* block; } ;
typedef  int u8 ;
typedef  int u16 ;
struct pmac_i2c_bus {int dummy; } ;
struct i2c_adapter {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int EINVAL ; 
#define  I2C_SMBUS_BLOCK_DATA 133 
#define  I2C_SMBUS_BYTE 132 
#define  I2C_SMBUS_BYTE_DATA 131 
#define  I2C_SMBUS_I2C_BLOCK_DATA 130 
#define  I2C_SMBUS_QUICK 129 
 char I2C_SMBUS_READ ; 
#define  I2C_SMBUS_WORD_DATA 128 
 struct pmac_i2c_bus* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  pmac_i2c_close (struct pmac_i2c_bus*) ; 
 int /*<<< orphan*/  pmac_i2c_mode_combined ; 
 int /*<<< orphan*/  pmac_i2c_mode_std ; 
 int /*<<< orphan*/  pmac_i2c_mode_stdsub ; 
 int pmac_i2c_open (struct pmac_i2c_bus*,int /*<<< orphan*/ ) ; 
 int pmac_i2c_setmode (struct pmac_i2c_bus*,int /*<<< orphan*/ ) ; 
 int pmac_i2c_xfer (struct pmac_i2c_bus*,int,int,int,int*,int) ; 

__attribute__((used)) static s32 i2c_powermac_smbus_xfer(	struct i2c_adapter*	adap,
					u16			addr,
					unsigned short		flags,
					char			read_write,
					u8			command,
					int			size,
					union i2c_smbus_data*	data)
{
	struct pmac_i2c_bus	*bus = i2c_get_adapdata(adap);
	int			rc = 0;
	int			read = (read_write == I2C_SMBUS_READ);
	int			addrdir = (addr << 1) | read;
	u8			local[2];

	rc = pmac_i2c_open(bus, 0);
	if (rc)
		return rc;

	switch (size) {
        case I2C_SMBUS_QUICK:
		rc = pmac_i2c_setmode(bus, pmac_i2c_mode_std);
		if (rc)
			goto bail;
		rc = pmac_i2c_xfer(bus, addrdir, 0, 0, NULL, 0);
	    	break;
        case I2C_SMBUS_BYTE:
		rc = pmac_i2c_setmode(bus, pmac_i2c_mode_std);
		if (rc)
			goto bail;
		rc = pmac_i2c_xfer(bus, addrdir, 0, 0, &data->byte, 1);
	    	break;
        case I2C_SMBUS_BYTE_DATA:
		rc = pmac_i2c_setmode(bus, read ?
				      pmac_i2c_mode_combined :
				      pmac_i2c_mode_stdsub);
		if (rc)
			goto bail;
		rc = pmac_i2c_xfer(bus, addrdir, 1, command, &data->byte, 1);
	    	break;
        case I2C_SMBUS_WORD_DATA:
		rc = pmac_i2c_setmode(bus, read ?
				      pmac_i2c_mode_combined :
				      pmac_i2c_mode_stdsub);
		if (rc)
			goto bail;
		if (!read) {
			local[0] = data->word & 0xff;
			local[1] = (data->word >> 8) & 0xff;
		}
		rc = pmac_i2c_xfer(bus, addrdir, 1, command, local, 2);
		if (rc == 0 && read) {
			data->word = ((u16)local[1]) << 8;
			data->word |= local[0];
		}
	    	break;

	/* Note that these are broken vs. the expected smbus API where
	 * on reads, the length is actually returned from the function,
	 * but I think the current API makes no sense and I don't want
	 * any driver that I haven't verified for correctness to go
	 * anywhere near a pmac i2c bus anyway ...
	 *
	 * I'm also not completely sure what kind of phases to do between
	 * the actual command and the data (what I am _supposed_ to do that
	 * is). For now, I assume writes are a single stream and reads have
	 * a repeat start/addr phase (but not stop in between)
	 */
        case I2C_SMBUS_BLOCK_DATA:
		rc = pmac_i2c_setmode(bus, read ?
				      pmac_i2c_mode_combined :
				      pmac_i2c_mode_stdsub);
		if (rc)
			goto bail;
		rc = pmac_i2c_xfer(bus, addrdir, 1, command, data->block,
				   data->block[0] + 1);

		break;
	case I2C_SMBUS_I2C_BLOCK_DATA:
		rc = pmac_i2c_setmode(bus, read ?
				      pmac_i2c_mode_combined :
				      pmac_i2c_mode_stdsub);
		if (rc)
			goto bail;
		rc = pmac_i2c_xfer(bus, addrdir, 1, command,
				   &data->block[1], data->block[0]);
		break;

        default:
	    	rc = -EINVAL;
	}
 bail:
	pmac_i2c_close(bus);
	return rc;
}