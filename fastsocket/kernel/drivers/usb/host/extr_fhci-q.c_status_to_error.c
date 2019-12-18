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
typedef  int u32 ;

/* Variables and functions */
 int ECOMM ; 
 int EILSEQ ; 
 int EINVAL ; 
 int ENOSR ; 
 int EOVERFLOW ; 
 int EPIPE ; 
 int EPROTO ; 
 int EREMOTEIO ; 
 int ETIMEDOUT ; 
 int USB_TD_OK ; 
 int USB_TD_RX_DATA_OVERUN ; 
 int USB_TD_RX_DATA_UNDERUN ; 
 int USB_TD_RX_ER_BITSTUFF ; 
 int USB_TD_RX_ER_CRC ; 
 int USB_TD_RX_ER_NONOCT ; 
 int USB_TD_RX_ER_OVERUN ; 
 int USB_TD_RX_ER_PID ; 
 int USB_TD_TX_ER_NAK ; 
 int USB_TD_TX_ER_STALL ; 
 int USB_TD_TX_ER_TIMEOUT ; 
 int USB_TD_TX_ER_UNDERUN ; 

__attribute__((used)) static int status_to_error(u32 status)
{
	if (status == USB_TD_OK)
		return 0;
	else if (status & USB_TD_RX_ER_CRC)
		return -EILSEQ;
	else if (status & USB_TD_RX_ER_NONOCT)
		return -EPROTO;
	else if (status & USB_TD_RX_ER_OVERUN)
		return -ECOMM;
	else if (status & USB_TD_RX_ER_BITSTUFF)
		return -EPROTO;
	else if (status & USB_TD_RX_ER_PID)
		return -EILSEQ;
	else if (status & (USB_TD_TX_ER_NAK | USB_TD_TX_ER_TIMEOUT))
		return -ETIMEDOUT;
	else if (status & USB_TD_TX_ER_STALL)
		return -EPIPE;
	else if (status & USB_TD_TX_ER_UNDERUN)
		return -ENOSR;
	else if (status & USB_TD_RX_DATA_UNDERUN)
		return -EREMOTEIO;
	else if (status & USB_TD_RX_DATA_OVERUN)
		return -EOVERFLOW;
	else
		return -EINVAL;
}