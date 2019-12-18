#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ hbuf_out; scalar_t__ saved_hbuf_out; int /*<<< orphan*/  hlen_out; } ;
typedef  TYPE_1__ br_ssl_engine_context ;

/* Variables and functions */
 scalar_t__ br_ssl_engine_has_pld_to_send (TYPE_1__*) ; 
 int /*<<< orphan*/  sendpld_ack (TYPE_1__*,scalar_t__) ; 
 scalar_t__ sendpld_buf (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sendpld_flush (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
br_ssl_engine_flush_record(br_ssl_engine_context *cc)
{
	if (cc->hbuf_out != cc->saved_hbuf_out) {
		sendpld_ack(cc, cc->hbuf_out - cc->saved_hbuf_out);
	}
	if (br_ssl_engine_has_pld_to_send(cc)) {
		sendpld_flush(cc, 0);
	}
	cc->saved_hbuf_out = cc->hbuf_out = sendpld_buf(cc, &cc->hlen_out);
}