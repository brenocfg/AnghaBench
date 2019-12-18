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
typedef  int u16 ;
struct isdnhdlc_vars {int state; int bit_shift; int do_closing; int shift_reg; int data_received; int crc; scalar_t__ do_bitreverse; int ffvalue; int cbin; int data_bits; int hdlc_bits1; scalar_t__ do_adapt56; int /*<<< orphan*/  dchannel; } ;

/* Variables and functions */
#define  HDLC_SENDFLAG_B0 140 
#define  HDLC_SENDFLAG_B1A6 139 
#define  HDLC_SENDFLAG_B7 138 
#define  HDLC_SENDFLAG_ONE 137 
#define  HDLC_SEND_CLOSING_FLAG 136 
#define  HDLC_SEND_CRC1 135 
#define  HDLC_SEND_CRC2 134 
#define  HDLC_SEND_DATA 133 
#define  HDLC_SEND_FAST_FLAG 132 
#define  HDLC_SEND_FAST_IDLE 131 
#define  HDLC_SEND_FIRST_FLAG 130 
#define  HDLC_SEND_IDLE1 129 
#define  STOPPED 128 
 void* bitrev8 (int) ; 
 int crc_ccitt_byte (int,int) ; 

int isdnhdlc_encode(struct isdnhdlc_vars *hdlc, const u8 *src, u16 slen,
	int *count, u8 *dst, int dsize)
{
	static const unsigned char xfast_flag_value[] = {
		0x7e, 0x3f, 0x9f, 0xcf, 0xe7, 0xf3, 0xf9, 0xfc, 0x7e
	};

	int len = 0;

	*count = slen;

	/* special handling for one byte frames */
	if ((slen == 1) && (hdlc->state == HDLC_SEND_FAST_FLAG))
		hdlc->state = HDLC_SENDFLAG_ONE;
	while (dsize > 0) {
		if (hdlc->bit_shift == 0) {
			if (slen && !hdlc->do_closing) {
				hdlc->shift_reg = *src++;
				slen--;
				if (slen == 0)
					/* closing sequence, CRC + flag(s) */
					hdlc->do_closing = 1;
				hdlc->bit_shift = 8;
			} else {
				if (hdlc->state == HDLC_SEND_DATA) {
					if (hdlc->data_received) {
						hdlc->state = HDLC_SEND_CRC1;
						hdlc->crc ^= 0xffff;
						hdlc->bit_shift = 8;
						hdlc->shift_reg =
							hdlc->crc & 0xff;
					} else if (!hdlc->do_adapt56)
						hdlc->state =
							HDLC_SEND_FAST_FLAG;
					else
						hdlc->state =
							HDLC_SENDFLAG_B0;
				}

			}
		}

		switch (hdlc->state) {
		case STOPPED:
			while (dsize--)
				*dst++ = 0xff;
			return dsize;
		case HDLC_SEND_FAST_FLAG:
			hdlc->do_closing = 0;
			if (slen == 0) {
				/* the code is for bitreverse streams */
				if (hdlc->do_bitreverse == 0)
					*dst++ = bitrev8(hdlc->ffvalue);
				else
					*dst++ = hdlc->ffvalue;
				len++;
				dsize--;
				break;
			}
			/* fall through */
		case HDLC_SENDFLAG_ONE:
			if (hdlc->bit_shift == 8) {
				hdlc->cbin = hdlc->ffvalue >>
					(8 - hdlc->data_bits);
				hdlc->state = HDLC_SEND_DATA;
				hdlc->crc = 0xffff;
				hdlc->hdlc_bits1 = 0;
				hdlc->data_received = 1;
			}
			break;
		case HDLC_SENDFLAG_B0:
			hdlc->do_closing = 0;
			hdlc->cbin <<= 1;
			hdlc->data_bits++;
			hdlc->hdlc_bits1 = 0;
			hdlc->state = HDLC_SENDFLAG_B1A6;
			break;
		case HDLC_SENDFLAG_B1A6:
			hdlc->cbin <<= 1;
			hdlc->data_bits++;
			hdlc->cbin++;
			if (++hdlc->hdlc_bits1 == 6)
				hdlc->state = HDLC_SENDFLAG_B7;
			break;
		case HDLC_SENDFLAG_B7:
			hdlc->cbin <<= 1;
			hdlc->data_bits++;
			if (slen == 0) {
				hdlc->state = HDLC_SENDFLAG_B0;
				break;
			}
			if (hdlc->bit_shift == 8) {
				hdlc->state = HDLC_SEND_DATA;
				hdlc->crc = 0xffff;
				hdlc->hdlc_bits1 = 0;
				hdlc->data_received = 1;
			}
			break;
		case HDLC_SEND_FIRST_FLAG:
			hdlc->data_received = 1;
			if (hdlc->data_bits == 8) {
				hdlc->state = HDLC_SEND_DATA;
				hdlc->crc = 0xffff;
				hdlc->hdlc_bits1 = 0;
				break;
			}
			hdlc->cbin <<= 1;
			hdlc->data_bits++;
			if (hdlc->shift_reg & 0x01)
				hdlc->cbin++;
			hdlc->shift_reg >>= 1;
			hdlc->bit_shift--;
			if (hdlc->bit_shift == 0) {
				hdlc->state = HDLC_SEND_DATA;
				hdlc->crc = 0xffff;
				hdlc->hdlc_bits1 = 0;
			}
			break;
		case HDLC_SEND_DATA:
			hdlc->cbin <<= 1;
			hdlc->data_bits++;
			if (hdlc->hdlc_bits1 == 5) {
				hdlc->hdlc_bits1 = 0;
				break;
			}
			if (hdlc->bit_shift == 8)
				hdlc->crc = crc_ccitt_byte(hdlc->crc,
					hdlc->shift_reg);
			if (hdlc->shift_reg & 0x01) {
				hdlc->hdlc_bits1++;
				hdlc->cbin++;
				hdlc->shift_reg >>= 1;
				hdlc->bit_shift--;
			} else {
				hdlc->hdlc_bits1 = 0;
				hdlc->shift_reg >>= 1;
				hdlc->bit_shift--;
			}
			break;
		case HDLC_SEND_CRC1:
			hdlc->cbin <<= 1;
			hdlc->data_bits++;
			if (hdlc->hdlc_bits1 == 5) {
				hdlc->hdlc_bits1 = 0;
				break;
			}
			if (hdlc->shift_reg & 0x01) {
				hdlc->hdlc_bits1++;
				hdlc->cbin++;
				hdlc->shift_reg >>= 1;
				hdlc->bit_shift--;
			} else {
				hdlc->hdlc_bits1 = 0;
				hdlc->shift_reg >>= 1;
				hdlc->bit_shift--;
			}
			if (hdlc->bit_shift == 0) {
				hdlc->shift_reg = (hdlc->crc >> 8);
				hdlc->state = HDLC_SEND_CRC2;
				hdlc->bit_shift = 8;
			}
			break;
		case HDLC_SEND_CRC2:
			hdlc->cbin <<= 1;
			hdlc->data_bits++;
			if (hdlc->hdlc_bits1 == 5) {
				hdlc->hdlc_bits1 = 0;
				break;
			}
			if (hdlc->shift_reg & 0x01) {
				hdlc->hdlc_bits1++;
				hdlc->cbin++;
				hdlc->shift_reg >>= 1;
				hdlc->bit_shift--;
			} else {
				hdlc->hdlc_bits1 = 0;
				hdlc->shift_reg >>= 1;
				hdlc->bit_shift--;
			}
			if (hdlc->bit_shift == 0) {
				hdlc->shift_reg = 0x7e;
				hdlc->state = HDLC_SEND_CLOSING_FLAG;
				hdlc->bit_shift = 8;
			}
			break;
		case HDLC_SEND_CLOSING_FLAG:
			hdlc->cbin <<= 1;
			hdlc->data_bits++;
			if (hdlc->hdlc_bits1 == 5) {
				hdlc->hdlc_bits1 = 0;
				break;
			}
			if (hdlc->shift_reg & 0x01)
				hdlc->cbin++;
			hdlc->shift_reg >>= 1;
			hdlc->bit_shift--;
			if (hdlc->bit_shift == 0) {
				hdlc->ffvalue =
					xfast_flag_value[hdlc->data_bits];
				if (hdlc->dchannel) {
					hdlc->ffvalue = 0x7e;
					hdlc->state = HDLC_SEND_IDLE1;
					hdlc->bit_shift = 8-hdlc->data_bits;
					if (hdlc->bit_shift == 0)
						hdlc->state =
							HDLC_SEND_FAST_IDLE;
				} else {
					if (!hdlc->do_adapt56) {
						hdlc->state =
							HDLC_SEND_FAST_FLAG;
						hdlc->data_received = 0;
					} else {
						hdlc->state = HDLC_SENDFLAG_B0;
						hdlc->data_received = 0;
					}
					/* Finished this frame, send flags */
					if (dsize > 1)
						dsize = 1;
				}
			}
			break;
		case HDLC_SEND_IDLE1:
			hdlc->do_closing = 0;
			hdlc->cbin <<= 1;
			hdlc->cbin++;
			hdlc->data_bits++;
			hdlc->bit_shift--;
			if (hdlc->bit_shift == 0) {
				hdlc->state = HDLC_SEND_FAST_IDLE;
				hdlc->bit_shift = 0;
			}
			break;
		case HDLC_SEND_FAST_IDLE:
			hdlc->do_closing = 0;
			hdlc->cbin = 0xff;
			hdlc->data_bits = 8;
			if (hdlc->bit_shift == 8) {
				hdlc->cbin = 0x7e;
				hdlc->state = HDLC_SEND_FIRST_FLAG;
			} else {
				/* the code is for bitreverse streams */
				if (hdlc->do_bitreverse == 0)
					*dst++ = bitrev8(hdlc->cbin);
				else
					*dst++ = hdlc->cbin;
				hdlc->bit_shift = 0;
				hdlc->data_bits = 0;
				len++;
				dsize = 0;
			}
			break;
		default:
			break;
		}
		if (hdlc->do_adapt56) {
			if (hdlc->data_bits == 7) {
				hdlc->cbin <<= 1;
				hdlc->cbin++;
				hdlc->data_bits++;
			}
		}
		if (hdlc->data_bits == 8) {
			/* the code is for bitreverse streams */
			if (hdlc->do_bitreverse == 0)
				*dst++ = bitrev8(hdlc->cbin);
			else
				*dst++ = hdlc->cbin;
			hdlc->data_bits = 0;
			len++;
			dsize--;
		}
	}
	*count -= slen;

	return len;
}