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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ data; } ;
struct rfcomm_session {int dummy; } ;
struct rfcomm_rpn {scalar_t__ bit_rate; scalar_t__ flow_ctrl; scalar_t__ xon_char; scalar_t__ xoff_char; int param_mask; int /*<<< orphan*/  line_settings; int /*<<< orphan*/  dlci; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,scalar_t__,...) ; 
 scalar_t__ RFCOMM_RPN_BR_115200 ; 
 scalar_t__ RFCOMM_RPN_DATA_8 ; 
 scalar_t__ RFCOMM_RPN_FLOW_NONE ; 
 scalar_t__ RFCOMM_RPN_PARITY_NONE ; 
 int /*<<< orphan*/  RFCOMM_RPN_PM_ALL ; 
 int /*<<< orphan*/  RFCOMM_RPN_PM_BITRATE ; 
 int /*<<< orphan*/  RFCOMM_RPN_PM_DATA ; 
 int /*<<< orphan*/  RFCOMM_RPN_PM_FLOW ; 
 int /*<<< orphan*/  RFCOMM_RPN_PM_PARITY ; 
 int /*<<< orphan*/  RFCOMM_RPN_PM_STOP ; 
 int /*<<< orphan*/  RFCOMM_RPN_PM_XOFF ; 
 int /*<<< orphan*/  RFCOMM_RPN_PM_XON ; 
 scalar_t__ RFCOMM_RPN_STOP_1 ; 
 scalar_t__ RFCOMM_RPN_XOFF_CHAR ; 
 scalar_t__ RFCOMM_RPN_XON_CHAR ; 
 scalar_t__ __get_dlci (int /*<<< orphan*/ ) ; 
 scalar_t__ __get_rpn_data_bits (int /*<<< orphan*/ ) ; 
 scalar_t__ __get_rpn_parity (int /*<<< orphan*/ ) ; 
 scalar_t__ __get_rpn_stop_bits (int /*<<< orphan*/ ) ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_send_rpn (struct rfcomm_session*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rfcomm_recv_rpn(struct rfcomm_session *s, int cr, int len, struct sk_buff *skb)
{
	struct rfcomm_rpn *rpn = (void *) skb->data;
	u8 dlci = __get_dlci(rpn->dlci);

	u8 bit_rate  = 0;
	u8 data_bits = 0;
	u8 stop_bits = 0;
	u8 parity    = 0;
	u8 flow_ctrl = 0;
	u8 xon_char  = 0;
	u8 xoff_char = 0;
	u16 rpn_mask = RFCOMM_RPN_PM_ALL;

	BT_DBG("dlci %d cr %d len 0x%x bitr 0x%x line 0x%x flow 0x%x xonc 0x%x xoffc 0x%x pm 0x%x",
		dlci, cr, len, rpn->bit_rate, rpn->line_settings, rpn->flow_ctrl,
		rpn->xon_char, rpn->xoff_char, rpn->param_mask);

	if (!cr)
		return 0;

	if (len == 1) {
		/* This is a request, return default settings */
		bit_rate  = RFCOMM_RPN_BR_115200;
		data_bits = RFCOMM_RPN_DATA_8;
		stop_bits = RFCOMM_RPN_STOP_1;
		parity    = RFCOMM_RPN_PARITY_NONE;
		flow_ctrl = RFCOMM_RPN_FLOW_NONE;
		xon_char  = RFCOMM_RPN_XON_CHAR;
		xoff_char = RFCOMM_RPN_XOFF_CHAR;
		goto rpn_out;
	}

	/* Check for sane values, ignore/accept bit_rate, 8 bits, 1 stop bit,
	 * no parity, no flow control lines, normal XON/XOFF chars */

	if (rpn->param_mask & cpu_to_le16(RFCOMM_RPN_PM_BITRATE)) {
		bit_rate = rpn->bit_rate;
		if (bit_rate != RFCOMM_RPN_BR_115200) {
			BT_DBG("RPN bit rate mismatch 0x%x", bit_rate);
			bit_rate = RFCOMM_RPN_BR_115200;
			rpn_mask ^= RFCOMM_RPN_PM_BITRATE;
		}
	}

	if (rpn->param_mask & cpu_to_le16(RFCOMM_RPN_PM_DATA)) {
		data_bits = __get_rpn_data_bits(rpn->line_settings);
		if (data_bits != RFCOMM_RPN_DATA_8) {
			BT_DBG("RPN data bits mismatch 0x%x", data_bits);
			data_bits = RFCOMM_RPN_DATA_8;
			rpn_mask ^= RFCOMM_RPN_PM_DATA;
		}
	}

	if (rpn->param_mask & cpu_to_le16(RFCOMM_RPN_PM_STOP)) {
		stop_bits = __get_rpn_stop_bits(rpn->line_settings);
		if (stop_bits != RFCOMM_RPN_STOP_1) {
			BT_DBG("RPN stop bits mismatch 0x%x", stop_bits);
			stop_bits = RFCOMM_RPN_STOP_1;
			rpn_mask ^= RFCOMM_RPN_PM_STOP;
		}
	}

	if (rpn->param_mask & cpu_to_le16(RFCOMM_RPN_PM_PARITY)) {
		parity = __get_rpn_parity(rpn->line_settings);
		if (parity != RFCOMM_RPN_PARITY_NONE) {
			BT_DBG("RPN parity mismatch 0x%x", parity);
			parity = RFCOMM_RPN_PARITY_NONE;
			rpn_mask ^= RFCOMM_RPN_PM_PARITY;
		}
	}

	if (rpn->param_mask & cpu_to_le16(RFCOMM_RPN_PM_FLOW)) {
		flow_ctrl = rpn->flow_ctrl;
		if (flow_ctrl != RFCOMM_RPN_FLOW_NONE) {
			BT_DBG("RPN flow ctrl mismatch 0x%x", flow_ctrl);
			flow_ctrl = RFCOMM_RPN_FLOW_NONE;
			rpn_mask ^= RFCOMM_RPN_PM_FLOW;
		}
	}

	if (rpn->param_mask & cpu_to_le16(RFCOMM_RPN_PM_XON)) {
		xon_char = rpn->xon_char;
		if (xon_char != RFCOMM_RPN_XON_CHAR) {
			BT_DBG("RPN XON char mismatch 0x%x", xon_char);
			xon_char = RFCOMM_RPN_XON_CHAR;
			rpn_mask ^= RFCOMM_RPN_PM_XON;
		}
	}

	if (rpn->param_mask & cpu_to_le16(RFCOMM_RPN_PM_XOFF)) {
		xoff_char = rpn->xoff_char;
		if (xoff_char != RFCOMM_RPN_XOFF_CHAR) {
			BT_DBG("RPN XOFF char mismatch 0x%x", xoff_char);
			xoff_char = RFCOMM_RPN_XOFF_CHAR;
			rpn_mask ^= RFCOMM_RPN_PM_XOFF;
		}
	}

rpn_out:
	rfcomm_send_rpn(s, 0, dlci, bit_rate, data_bits, stop_bits,
			parity, flow_ctrl, xon_char, xoff_char, rpn_mask);

	return 0;
}