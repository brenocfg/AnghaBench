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
typedef  int u16 ;
struct radeon_i2c_chan {int dummy; } ;
struct i2c_algo_dp_aux_data {int address; } ;
struct i2c_adapter {struct i2c_algo_dp_aux_data* algo_data; } ;

/* Variables and functions */
 int AUX_I2C_MOT ; 
 int AUX_I2C_READ ; 
#define  AUX_I2C_REPLY_ACK 135 
#define  AUX_I2C_REPLY_DEFER 134 
 int AUX_I2C_REPLY_MASK ; 
#define  AUX_I2C_REPLY_NACK 133 
 int AUX_I2C_WRITE ; 
#define  AUX_NATIVE_REPLY_ACK 132 
#define  AUX_NATIVE_REPLY_DEFER 131 
 int AUX_NATIVE_REPLY_MASK ; 
#define  AUX_NATIVE_REPLY_NACK 130 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EBUSY ; 
 int EREMOTEIO ; 
#define  MODE_I2C_READ 129 
 int MODE_I2C_STOP ; 
#define  MODE_I2C_WRITE 128 
 int radeon_process_aux_ch (struct radeon_i2c_chan*,int*,int,int*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  udelay (int) ; 

int radeon_dp_i2c_aux_ch(struct i2c_adapter *adapter, int mode,
			 u8 write_byte, u8 *read_byte)
{
	struct i2c_algo_dp_aux_data *algo_data = adapter->algo_data;
	struct radeon_i2c_chan *auxch = (struct radeon_i2c_chan *)adapter;
	u16 address = algo_data->address;
	u8 msg[5];
	u8 reply[2];
	unsigned retry;
	int msg_bytes;
	int reply_bytes = 1;
	int ret;
	u8 ack;

	/* Set up the command byte */
	if (mode & MODE_I2C_READ)
		msg[2] = AUX_I2C_READ << 4;
	else
		msg[2] = AUX_I2C_WRITE << 4;

	if (!(mode & MODE_I2C_STOP))
		msg[2] |= AUX_I2C_MOT << 4;

	msg[0] = address;
	msg[1] = address >> 8;

	switch (mode) {
	case MODE_I2C_WRITE:
		msg_bytes = 5;
		msg[3] = msg_bytes << 4;
		msg[4] = write_byte;
		break;
	case MODE_I2C_READ:
		msg_bytes = 4;
		msg[3] = msg_bytes << 4;
		break;
	default:
		msg_bytes = 4;
		msg[3] = 3 << 4;
		break;
	}

	for (retry = 0; retry < 4; retry++) {
		ret = radeon_process_aux_ch(auxch,
					    msg, msg_bytes, reply, reply_bytes, 0, &ack);
		if (ret == -EBUSY)
			continue;
		else if (ret < 0) {
			DRM_DEBUG_KMS("aux_ch failed %d\n", ret);
			return ret;
		}

		switch (ack & AUX_NATIVE_REPLY_MASK) {
		case AUX_NATIVE_REPLY_ACK:
			/* I2C-over-AUX Reply field is only valid
			 * when paired with AUX ACK.
			 */
			break;
		case AUX_NATIVE_REPLY_NACK:
			DRM_DEBUG_KMS("aux_ch native nack\n");
			return -EREMOTEIO;
		case AUX_NATIVE_REPLY_DEFER:
			DRM_DEBUG_KMS("aux_ch native defer\n");
			udelay(400);
			continue;
		default:
			DRM_ERROR("aux_ch invalid native reply 0x%02x\n", ack);
			return -EREMOTEIO;
		}

		switch (ack & AUX_I2C_REPLY_MASK) {
		case AUX_I2C_REPLY_ACK:
			if (mode == MODE_I2C_READ)
				*read_byte = reply[0];
			return ret;
		case AUX_I2C_REPLY_NACK:
			DRM_DEBUG_KMS("aux_i2c nack\n");
			return -EREMOTEIO;
		case AUX_I2C_REPLY_DEFER:
			DRM_DEBUG_KMS("aux_i2c defer\n");
			udelay(400);
			break;
		default:
			DRM_ERROR("aux_i2c invalid reply 0x%02x\n", ack);
			return -EREMOTEIO;
		}
	}

	DRM_DEBUG_KMS("aux i2c too many retries, giving up\n");
	return -EREMOTEIO;
}