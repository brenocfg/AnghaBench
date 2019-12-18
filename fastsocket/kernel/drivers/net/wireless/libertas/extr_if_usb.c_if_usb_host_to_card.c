#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint16_t ;
struct lbs_private {int /*<<< orphan*/  dnld_sent; struct if_usb_card* card; } ;
struct if_usb_card {scalar_t__ ep_out_buf; TYPE_1__* udev; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_TYPE_DATA ; 
 int /*<<< orphan*/  CMD_TYPE_REQUEST ; 
 int /*<<< orphan*/  DNLD_CMD_SENT ; 
 int /*<<< orphan*/  DNLD_DATA_SENT ; 
 scalar_t__ MESSAGE_HEADER_LEN ; 
 scalar_t__ MVMS_CMD ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_usbd (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__*,scalar_t__) ; 
 int usb_tx_block (struct if_usb_card*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int if_usb_host_to_card(struct lbs_private *priv, uint8_t type,
			       uint8_t *payload, uint16_t nb)
{
	struct if_usb_card *cardp = priv->card;

	lbs_deb_usbd(&cardp->udev->dev,"*** type = %u\n", type);
	lbs_deb_usbd(&cardp->udev->dev,"size after = %d\n", nb);

	if (type == MVMS_CMD) {
		*(__le32 *)cardp->ep_out_buf = cpu_to_le32(CMD_TYPE_REQUEST);
		priv->dnld_sent = DNLD_CMD_SENT;
	} else {
		*(__le32 *)cardp->ep_out_buf = cpu_to_le32(CMD_TYPE_DATA);
		priv->dnld_sent = DNLD_DATA_SENT;
	}

	memcpy((cardp->ep_out_buf + MESSAGE_HEADER_LEN), payload, nb);

	return usb_tx_block(cardp, cardp->ep_out_buf, nb + MESSAGE_HEADER_LEN);
}