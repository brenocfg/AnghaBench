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
struct isdnhdlc_vars {int bit_shift; scalar_t__ do_bitreverse; int cbin; int state; int hdlc_bits1; int crc; int shift_reg; int data_bits; int data_received; int dstpos; int ffvalue; int ffbit_shift; scalar_t__ do_adapt56; } ;

/* Variables and functions */
#define  HDLC_FAST_FLAG 134 
#define  HDLC_FAST_IDLE 133 
 int HDLC_FRAMING_ERROR ; 
#define  HDLC_GETFLAG_B1A6 132 
#define  HDLC_GETFLAG_B7 131 
#define  HDLC_GET_DATA 130 
#define  HDLC_GET_FLAG_B0 129 
 int HDLC_LENGTH_ERROR ; 
#define  STOPPED 128 
 int bitrev8 (int /*<<< orphan*/ ) ; 
 int check_frame (struct isdnhdlc_vars*) ; 
 int crc_ccitt_byte (int,int) ; 
 int /*<<< orphan*/  handle_abort (struct isdnhdlc_vars*) ; 
 int /*<<< orphan*/  handle_fast_flag (struct isdnhdlc_vars*) ; 

int isdnhdlc_decode(struct isdnhdlc_vars *hdlc, const u8 *src, int slen,
	int *count, u8 *dst, int dsize)
{
	int status = 0;

	static const unsigned char fast_flag[] = {
		0x00, 0x00, 0x00, 0x20, 0x30, 0x38, 0x3c, 0x3e, 0x3f
	};

	static const unsigned char fast_flag_value[] = {
		0x00, 0x7e, 0xfc, 0xf9, 0xf3, 0xe7, 0xcf, 0x9f, 0x3f
	};

	static const unsigned char fast_abort[] = {
		0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff
	};

#define handle_fast_flag(h) \
	do {\
		if (h->cbin == fast_flag[h->bit_shift]) {\
			h->ffvalue = fast_flag_value[h->bit_shift];\
			h->state = HDLC_FAST_FLAG;\
			h->ffbit_shift = h->bit_shift;\
			h->bit_shift = 1;\
		} else {\
			h->state = HDLC_GET_DATA;\
			h->data_received = 0;\
		} \
	} while (0)

#define handle_abort(h) \
	do {\
		h->shift_reg = fast_abort[h->ffbit_shift - 1];\
		h->hdlc_bits1 = h->ffbit_shift - 2;\
		if (h->hdlc_bits1 < 0)\
			h->hdlc_bits1 = 0;\
		h->data_bits = h->ffbit_shift - 1;\
		h->state = HDLC_GET_DATA;\
		h->data_received = 0;\
	} while (0)

	*count = slen;

	while (slen > 0) {
		if (hdlc->bit_shift == 0) {
			/* the code is for bitreverse streams */
			if (hdlc->do_bitreverse == 0)
				hdlc->cbin = bitrev8(*src++);
			else
				hdlc->cbin = *src++;
			slen--;
			hdlc->bit_shift = 8;
			if (hdlc->do_adapt56)
				hdlc->bit_shift--;
		}

		switch (hdlc->state) {
		case STOPPED:
			return 0;
		case HDLC_FAST_IDLE:
			if (hdlc->cbin == 0xff) {
				hdlc->bit_shift = 0;
				break;
			}
			hdlc->state = HDLC_GET_FLAG_B0;
			hdlc->hdlc_bits1 = 0;
			hdlc->bit_shift = 8;
			break;
		case HDLC_GET_FLAG_B0:
			if (!(hdlc->cbin & 0x80)) {
				hdlc->state = HDLC_GETFLAG_B1A6;
				hdlc->hdlc_bits1 = 0;
			} else {
				if ((!hdlc->do_adapt56) &&
				    (++hdlc->hdlc_bits1 >= 8) &&
				    (hdlc->bit_shift == 1))
						hdlc->state = HDLC_FAST_IDLE;
			}
			hdlc->cbin <<= 1;
			hdlc->bit_shift--;
			break;
		case HDLC_GETFLAG_B1A6:
			if (hdlc->cbin & 0x80) {
				hdlc->hdlc_bits1++;
				if (hdlc->hdlc_bits1 == 6)
					hdlc->state = HDLC_GETFLAG_B7;
			} else
				hdlc->hdlc_bits1 = 0;
			hdlc->cbin <<= 1;
			hdlc->bit_shift--;
			break;
		case HDLC_GETFLAG_B7:
			if (hdlc->cbin & 0x80) {
				hdlc->state = HDLC_GET_FLAG_B0;
			} else {
				hdlc->state = HDLC_GET_DATA;
				hdlc->crc = 0xffff;
				hdlc->shift_reg = 0;
				hdlc->hdlc_bits1 = 0;
				hdlc->data_bits = 0;
				hdlc->data_received = 0;
			}
			hdlc->cbin <<= 1;
			hdlc->bit_shift--;
			break;
		case HDLC_GET_DATA:
			if (hdlc->cbin & 0x80) {
				hdlc->hdlc_bits1++;
				switch (hdlc->hdlc_bits1) {
				case 6:
					break;
				case 7:
					if (hdlc->data_received)
						/* bad frame */
						status = -HDLC_FRAMING_ERROR;
					if (!hdlc->do_adapt56) {
						if (hdlc->cbin == fast_abort
						    [hdlc->bit_shift + 1]) {
							hdlc->state =
								HDLC_FAST_IDLE;
							hdlc->bit_shift = 1;
							break;
						}
					} else
						hdlc->state = HDLC_GET_FLAG_B0;
					break;
				default:
					hdlc->shift_reg >>= 1;
					hdlc->shift_reg |= 0x80;
					hdlc->data_bits++;
					break;
				}
			} else {
				switch (hdlc->hdlc_bits1) {
				case 5:
					break;
				case 6:
					if (hdlc->data_received)
						status = check_frame(hdlc);
					hdlc->crc = 0xffff;
					hdlc->shift_reg = 0;
					hdlc->data_bits = 0;
					if (!hdlc->do_adapt56)
						handle_fast_flag(hdlc);
					else {
						hdlc->state = HDLC_GET_DATA;
						hdlc->data_received = 0;
					}
					break;
				default:
					hdlc->shift_reg >>= 1;
					hdlc->data_bits++;
					break;
				}
				hdlc->hdlc_bits1 = 0;
			}
			if (status) {
				hdlc->dstpos = 0;
				*count -= slen;
				hdlc->cbin <<= 1;
				hdlc->bit_shift--;
				return status;
			}
			if (hdlc->data_bits == 8) {
				hdlc->data_bits = 0;
				hdlc->data_received = 1;
				hdlc->crc = crc_ccitt_byte(hdlc->crc,
						hdlc->shift_reg);

				/* good byte received */
				if (hdlc->dstpos < dsize)
					dst[hdlc->dstpos++] = hdlc->shift_reg;
				else {
					/* frame too long */
					status = -HDLC_LENGTH_ERROR;
					hdlc->dstpos = 0;
				}
			}
			hdlc->cbin <<= 1;
			hdlc->bit_shift--;
			break;
		case HDLC_FAST_FLAG:
			if (hdlc->cbin == hdlc->ffvalue) {
				hdlc->bit_shift = 0;
				break;
			} else {
				if (hdlc->cbin == 0xff) {
					hdlc->state = HDLC_FAST_IDLE;
					hdlc->bit_shift = 0;
				} else if (hdlc->ffbit_shift == 8) {
					hdlc->state = HDLC_GETFLAG_B7;
					break;
				} else
					handle_abort(hdlc);
			}
			break;
		default:
			break;
		}
	}
	*count -= slen;
	return 0;
}