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
struct usb_hcd {int regs; } ;
struct isp1760_qtd {int packet_type; scalar_t__ length; int /*<<< orphan*/  data_buffer; } ;
struct isp1760_hcd {int dummy; } ;

/* Variables and functions */
 scalar_t__ HC_ATL_PL_SIZE ; 
#define  IN_PID 130 
#define  OUT_PID 129 
#define  SETUP_PID 128 
 struct usb_hcd* priv_to_hcd (struct isp1760_hcd*) ; 
 int /*<<< orphan*/  priv_write_copy (struct isp1760_hcd*,int /*<<< orphan*/ ,int,scalar_t__) ; 

__attribute__((used)) static void enqueue_one_qtd(struct isp1760_qtd *qtd, struct isp1760_hcd *priv,
		u32 payload)
{
	u32 token;
	struct usb_hcd *hcd = priv_to_hcd(priv);

	token = qtd->packet_type;

	if (qtd->length && (qtd->length <= HC_ATL_PL_SIZE)) {
		switch (token) {
		case IN_PID:
			break;
		case OUT_PID:
		case SETUP_PID:
			priv_write_copy(priv, qtd->data_buffer,
					hcd->regs + payload,
					qtd->length);
		}
	}
}