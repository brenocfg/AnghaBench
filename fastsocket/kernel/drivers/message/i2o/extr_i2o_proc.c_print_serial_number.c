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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct seq_file {int dummy; } ;

/* Variables and functions */
#define  I2O_SNFORMAT_ASCII 138 
#define  I2O_SNFORMAT_BINARY 137 
#define  I2O_SNFORMAT_DDM 136 
#define  I2O_SNFORMAT_IEEE_REG128 135 
#define  I2O_SNFORMAT_IEEE_REG64 134 
#define  I2O_SNFORMAT_LAN48_MAC 133 
#define  I2O_SNFORMAT_LAN64_MAC 132 
#define  I2O_SNFORMAT_UNICODE 131 
#define  I2O_SNFORMAT_UNKNOWN 130 
#define  I2O_SNFORMAT_UNKNOWN2 129 
#define  I2O_SNFORMAT_WAN 128 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static int print_serial_number(struct seq_file *seq, u8 * serialno, int max_len)
{
	int i;

	/* 19990419 -sralston
	 *      The I2O v1.5 (and v2.0 so far) "official specification"
	 *      got serial numbers WRONG!
	 *      Apparently, and despite what Section 3.4.4 says and
	 *      Figure 3-35 shows (pg 3-39 in the pdf doc),
	 *      the convention / consensus seems to be:
	 *        + First byte is SNFormat
	 *        + Second byte is SNLen (but only if SNFormat==7 (?))
	 *        + (v2.0) SCSI+BS may use IEEE Registered (64 or 128 bit) format
	 */
	switch (serialno[0]) {
	case I2O_SNFORMAT_BINARY:	/* Binary */
		seq_printf(seq, "0x");
		for (i = 0; i < serialno[1]; i++) {
			seq_printf(seq, "%02X", serialno[2 + i]);
		}
		break;

	case I2O_SNFORMAT_ASCII:	/* ASCII */
		if (serialno[1] < ' ') {	/* printable or SNLen? */
			/* sanity */
			max_len =
			    (max_len < serialno[1]) ? max_len : serialno[1];
			serialno[1 + max_len] = '\0';

			/* just print it */
			seq_printf(seq, "%s", &serialno[2]);
		} else {
			/* print chars for specified length */
			for (i = 0; i < serialno[1]; i++) {
				seq_printf(seq, "%c", serialno[2 + i]);
			}
		}
		break;

	case I2O_SNFORMAT_UNICODE:	/* UNICODE */
		seq_printf(seq, "UNICODE Format.  Can't Display\n");
		break;

	case I2O_SNFORMAT_LAN48_MAC:	/* LAN-48 MAC Address */
		seq_printf(seq,
			   "LAN-48 MAC address @ %02X:%02X:%02X:%02X:%02X:%02X",
			   serialno[2], serialno[3],
			   serialno[4], serialno[5], serialno[6], serialno[7]);
		break;

	case I2O_SNFORMAT_WAN:	/* WAN MAC Address */
		/* FIXME: Figure out what a WAN access address looks like?? */
		seq_printf(seq, "WAN Access Address");
		break;

/* plus new in v2.0 */
	case I2O_SNFORMAT_LAN64_MAC:	/* LAN-64 MAC Address */
		/* FIXME: Figure out what a LAN-64 address really looks like?? */
		seq_printf(seq,
			   "LAN-64 MAC address @ [?:%02X:%02X:?] %02X:%02X:%02X:%02X:%02X:%02X",
			   serialno[8], serialno[9],
			   serialno[2], serialno[3],
			   serialno[4], serialno[5], serialno[6], serialno[7]);
		break;

	case I2O_SNFORMAT_DDM:	/* I2O DDM */
		seq_printf(seq,
			   "DDM: Tid=%03Xh, Rsvd=%04Xh, OrgId=%04Xh",
			   *(u16 *) & serialno[2],
			   *(u16 *) & serialno[4], *(u16 *) & serialno[6]);
		break;

	case I2O_SNFORMAT_IEEE_REG64:	/* IEEE Registered (64-bit) */
	case I2O_SNFORMAT_IEEE_REG128:	/* IEEE Registered (128-bit) */
		/* FIXME: Figure if this is even close?? */
		seq_printf(seq,
			   "IEEE NodeName(hi,lo)=(%08Xh:%08Xh), PortName(hi,lo)=(%08Xh:%08Xh)\n",
			   *(u32 *) & serialno[2],
			   *(u32 *) & serialno[6],
			   *(u32 *) & serialno[10], *(u32 *) & serialno[14]);
		break;

	case I2O_SNFORMAT_UNKNOWN:	/* Unknown 0    */
	case I2O_SNFORMAT_UNKNOWN2:	/* Unknown 0xff */
	default:
		seq_printf(seq, "Unknown data format (0x%02x)", serialno[0]);
		break;
	}

	return 0;
}