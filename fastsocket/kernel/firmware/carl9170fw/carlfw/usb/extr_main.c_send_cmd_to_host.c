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
typedef  int uint8_t ;
struct TYPE_2__ {int len; int cmd; int ext; } ;
struct carl9170_cmd {int /*<<< orphan*/  data; TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,...) ; 
 scalar_t__ get_int_buf () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int const*,int const) ; 
 scalar_t__ unlikely (int const) ; 
 int /*<<< orphan*/  usb_trigger_in () ; 

void send_cmd_to_host(const uint8_t len, const uint8_t type,
		      const uint8_t ext, const uint8_t *body)
{
	struct carl9170_cmd *resp;

#ifdef CONFIG_CARL9170FW_DEBUG
	if (unlikely(len > sizeof(resp->data))) {
		DBG("CMD too long:%x %d\n", type, len);
		return ;
	}

	/* Element length must be a multiple of 4. */
	if (unlikely(len & 0x3)) {
		DBG("CMD length not mult. of 4:%x %d\n", type, len);
		return ;
	}
#endif /* CONFIG_CARL9170FW_DEBUG */

	resp = (struct carl9170_cmd *) get_int_buf();
	if (unlikely(resp == NULL)) {
		/* not very helpful for NON UART users */
		DBG("out of msg buffers\n");
		return ;
	}

	resp->hdr.len = len;
	resp->hdr.cmd = type;
	resp->hdr.ext = ext;

	memcpy(resp->data, body, len);
	usb_trigger_in();
}