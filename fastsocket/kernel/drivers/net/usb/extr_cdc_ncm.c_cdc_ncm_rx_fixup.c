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
struct usbnet {scalar_t__* data; } ;
struct usb_cdc_ncm_ndp16 {int /*<<< orphan*/  wNextNdpIndex; struct usb_cdc_ncm_dpe16* dpe16; int /*<<< orphan*/  dwSignature; } ;
struct usb_cdc_ncm_dpe16 {int /*<<< orphan*/  wDatagramLength; int /*<<< orphan*/  wDatagramIndex; } ;
struct sk_buff {int len; int /*<<< orphan*/ * data; } ;
struct cdc_ncm_ctx {int rx_max; } ;

/* Variables and functions */
 int ETH_HLEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ USB_CDC_NCM_NDP16_NOCRC_SIGN ; 
 int cdc_ncm_rx_verify_ndp16 (struct sk_buff*,int) ; 
 int cdc_ncm_rx_verify_nth16 (struct cdc_ncm_ctx*,struct sk_buff*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_tail_pointer (struct sk_buff*,int) ; 
 int /*<<< orphan*/  usbnet_skb_return (struct usbnet*,struct sk_buff*) ; 

__attribute__((used)) static int cdc_ncm_rx_fixup(struct usbnet *dev, struct sk_buff *skb_in)
{
	struct sk_buff *skb;
	struct cdc_ncm_ctx *ctx = (struct cdc_ncm_ctx *)dev->data[0];
	int len;
	int nframes;
	int x;
	int offset;
	struct usb_cdc_ncm_ndp16 *ndp16;
	struct usb_cdc_ncm_dpe16 *dpe16;
	int ndpoffset;
	int loopcount = 50; /* arbitrary max preventing infinite loop */

	ndpoffset = cdc_ncm_rx_verify_nth16(ctx, skb_in);
	if (ndpoffset < 0)
		goto error;

next_ndp:
	nframes = cdc_ncm_rx_verify_ndp16(skb_in, ndpoffset);
	if (nframes < 0)
		goto error;

	ndp16 = (struct usb_cdc_ncm_ndp16 *)(skb_in->data + ndpoffset);

	if (le32_to_cpu(ndp16->dwSignature) != USB_CDC_NCM_NDP16_NOCRC_SIGN) {
		pr_debug("invalid DPT16 signature <%u>\n",
			 le32_to_cpu(ndp16->dwSignature));
		goto err_ndp;
	}
	dpe16 = ndp16->dpe16;

	for (x = 0; x < nframes; x++, dpe16++) {
		offset = le16_to_cpu(dpe16->wDatagramIndex);
		len = le16_to_cpu(dpe16->wDatagramLength);

		/*
		 * CDC NCM ch. 3.7
		 * All entries after first NULL entry are to be ignored
		 */
		if ((offset == 0) || (len == 0)) {
			if (!x)
				goto err_ndp; /* empty NTB */
			break;
		}

		/* sanity checking */
		if (((offset + len) > skb_in->len) ||
				(len > ctx->rx_max) || (len < ETH_HLEN)) {
			pr_debug("invalid frame detected (ignored)"
					"offset[%u]=%u, length=%u, skb=%p\n",
					x, offset, len, skb_in);
			if (!x)
				goto err_ndp;
			break;

		} else {
			skb = skb_clone(skb_in, GFP_ATOMIC);
			if (!skb)
				goto error;
			skb->len = len;
			skb->data = ((u8 *)skb_in->data) + offset;
			skb_set_tail_pointer(skb, len);
			usbnet_skb_return(dev, skb);
		}
	}
err_ndp:
	/* are there more NDPs to process? */
	ndpoffset = le16_to_cpu(ndp16->wNextNdpIndex);
	if (ndpoffset && loopcount--)
		goto next_ndp;

	return 1;
error:
	return 0;
}