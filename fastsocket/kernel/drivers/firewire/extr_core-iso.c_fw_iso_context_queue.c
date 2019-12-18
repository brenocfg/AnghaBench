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
struct fw_iso_packet {int dummy; } ;
struct fw_iso_context {struct fw_card* card; } ;
struct fw_iso_buffer {int dummy; } ;
struct fw_card {TYPE_1__* driver; } ;
struct TYPE_2__ {int (* queue_iso ) (struct fw_iso_context*,struct fw_iso_packet*,struct fw_iso_buffer*,unsigned long) ;} ;

/* Variables and functions */
 int stub1 (struct fw_iso_context*,struct fw_iso_packet*,struct fw_iso_buffer*,unsigned long) ; 

int fw_iso_context_queue(struct fw_iso_context *ctx,
			 struct fw_iso_packet *packet,
			 struct fw_iso_buffer *buffer,
			 unsigned long payload)
{
	struct fw_card *card = ctx->card;

	return card->driver->queue_iso(ctx, packet, buffer, payload);
}