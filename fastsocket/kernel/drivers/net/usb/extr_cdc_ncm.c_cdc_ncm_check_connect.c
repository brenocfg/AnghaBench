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
struct usbnet {scalar_t__* data; } ;
struct cdc_ncm_ctx {int /*<<< orphan*/  connected; } ;

/* Variables and functions */

__attribute__((used)) static int cdc_ncm_check_connect(struct usbnet *dev)
{
	struct cdc_ncm_ctx *ctx;

	ctx = (struct cdc_ncm_ctx *)dev->data[0];
	if (ctx == NULL)
		return 1;	/* disconnected */

	return !ctx->connected;
}