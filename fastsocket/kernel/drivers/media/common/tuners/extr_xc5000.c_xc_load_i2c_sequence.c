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
struct xc5000_priv {int dummy; } ;
struct dvb_frontend {struct xc5000_priv* tuner_priv; } ;

/* Variables and functions */
 int XC_MAX_I2C_WRITE_LENGTH ; 
 int XC_RESULT_SUCCESS ; 
 int xc5000_TunerReset (struct dvb_frontend*) ; 
 int xc_send_i2c_data (struct xc5000_priv*,int*,int) ; 
 int /*<<< orphan*/  xc_wait (unsigned int) ; 

__attribute__((used)) static int xc_load_i2c_sequence(struct dvb_frontend *fe, const u8 *i2c_sequence)
{
	struct xc5000_priv *priv = fe->tuner_priv;

	int i, nbytes_to_send, result;
	unsigned int len, pos, index;
	u8 buf[XC_MAX_I2C_WRITE_LENGTH];

	index = 0;
	while ((i2c_sequence[index] != 0xFF) ||
		(i2c_sequence[index + 1] != 0xFF)) {
		len = i2c_sequence[index] * 256 + i2c_sequence[index+1];
		if (len == 0x0000) {
			/* RESET command */
			result = xc5000_TunerReset(fe);
			index += 2;
			if (result != XC_RESULT_SUCCESS)
				return result;
		} else if (len & 0x8000) {
			/* WAIT command */
			xc_wait(len & 0x7FFF);
			index += 2;
		} else {
			/* Send i2c data whilst ensuring individual transactions
			 * do not exceed XC_MAX_I2C_WRITE_LENGTH bytes.
			 */
			index += 2;
			buf[0] = i2c_sequence[index];
			buf[1] = i2c_sequence[index + 1];
			pos = 2;
			while (pos < len) {
				if ((len - pos) > XC_MAX_I2C_WRITE_LENGTH - 2)
					nbytes_to_send =
						XC_MAX_I2C_WRITE_LENGTH;
				else
					nbytes_to_send = (len - pos + 2);
				for (i = 2; i < nbytes_to_send; i++) {
					buf[i] = i2c_sequence[index + pos +
						i - 2];
				}
				result = xc_send_i2c_data(priv, buf,
					nbytes_to_send);

				if (result != XC_RESULT_SUCCESS)
					return result;

				pos += nbytes_to_send - 2;
			}
			index += len;
		}
	}
	return XC_RESULT_SUCCESS;
}