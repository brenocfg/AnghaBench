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
struct usb_cdc_ncm_ndp16 {int /*<<< orphan*/  wLength; int /*<<< orphan*/  dwSignature; } ;
struct usb_cdc_ncm_dpe16 {int dummy; } ;
struct sk_buff {int len; scalar_t__ data; } ;

/* Variables and functions */
 int EINVAL ; 
 int USB_CDC_NCM_NDP16_LENGTH_MIN ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

int cdc_ncm_rx_verify_ndp16(struct sk_buff *skb_in, int ndpoffset)
{
	struct usb_cdc_ncm_ndp16 *ndp16;
	int ret = -EINVAL;

	if ((ndpoffset + sizeof(struct usb_cdc_ncm_ndp16)) > skb_in->len) {
		pr_debug("invalid NDP offset  <%u>\n", ndpoffset);
		goto error;
	}
	ndp16 = (struct usb_cdc_ncm_ndp16 *)(skb_in->data + ndpoffset);

	if (le16_to_cpu(ndp16->wLength) < USB_CDC_NCM_NDP16_LENGTH_MIN) {
		pr_debug("invalid DPT16 length <%u>\n",
					le32_to_cpu(ndp16->dwSignature));
		goto error;
	}

	ret = ((le16_to_cpu(ndp16->wLength) -
					sizeof(struct usb_cdc_ncm_ndp16)) /
					sizeof(struct usb_cdc_ncm_dpe16));
	ret--; /* we process NDP entries except for the last one */

	if ((sizeof(struct usb_cdc_ncm_ndp16) + ret * (sizeof(struct usb_cdc_ncm_dpe16))) >
								skb_in->len) {
		pr_debug("Invalid nframes = %d\n", ret);
		ret = -EINVAL;
	}

error:
	return ret;
}