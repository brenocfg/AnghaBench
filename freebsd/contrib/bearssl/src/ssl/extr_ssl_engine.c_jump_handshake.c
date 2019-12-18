#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ record_type_in; size_t hlen_in; size_t hlen_out; int action; int /*<<< orphan*/ * saved_hbuf_out; int /*<<< orphan*/ * hbuf_out; int /*<<< orphan*/  cpu; int /*<<< orphan*/  (* hsrun ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/ * hbuf_in; } ;
typedef  TYPE_1__ br_ssl_engine_context ;

/* Variables and functions */
 scalar_t__ BR_SSL_APPLICATION_DATA ; 
 scalar_t__ br_ssl_engine_closed (TYPE_1__*) ; 
 scalar_t__ br_ssl_engine_has_pld_to_send (TYPE_1__*) ; 
 int /*<<< orphan*/  recvpld_ack (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/ * recvpld_buf (TYPE_1__*,size_t*) ; 
 int /*<<< orphan*/  sendpld_ack (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sendpld_buf (TYPE_1__*,size_t*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
jump_handshake(br_ssl_engine_context *cc, int action)
{
	/*
	 * We use a loop because the handshake processor actions may
	 * allow for more actions; namely, if the processor reads all
	 * input data, then it may allow for output data to be produced,
	 * in case of a shared in/out buffer.
	 */
	for (;;) {
		size_t hlen_in, hlen_out;

		/*
		 * Get input buffer. We do not want to provide
		 * application data to the handshake processor (we could
		 * get called with an explicit close or renegotiation
		 * while there is application data ready to be read).
		 */
		cc->hbuf_in = recvpld_buf(cc, &hlen_in);
		if (cc->hbuf_in != NULL
			&& cc->record_type_in == BR_SSL_APPLICATION_DATA)
		{
			hlen_in = 0;
		}

		/*
		 * Get output buffer. The handshake processor never
		 * leaves an unfinished outgoing record, so if there is
		 * buffered output, then it MUST be some application
		 * data, so the processor cannot write to it.
		 */
		cc->saved_hbuf_out = cc->hbuf_out = sendpld_buf(cc, &hlen_out);
		if (cc->hbuf_out != NULL && br_ssl_engine_has_pld_to_send(cc)) {
			hlen_out = 0;
		}

		/*
		 * Note: hlen_in and hlen_out can be both non-zero only if
		 * the input and output buffers are disjoint. Thus, we can
		 * offer both buffers to the handshake code.
		 */

		cc->hlen_in = hlen_in;
		cc->hlen_out = hlen_out;
		cc->action = action;
		cc->hsrun(&cc->cpu);
		if (br_ssl_engine_closed(cc)) {
			return;
		}
		if (cc->hbuf_out != cc->saved_hbuf_out) {
			sendpld_ack(cc, cc->hbuf_out - cc->saved_hbuf_out);
		}
		if (hlen_in != cc->hlen_in) {
			recvpld_ack(cc, hlen_in - cc->hlen_in);
			if (cc->hlen_in == 0) {
				/*
				 * We read all data bytes, which may have
				 * released the output buffer in case it
				 * is shared with the input buffer, and
				 * the handshake code might be waiting for
				 * that.
				 */
				action = 0;
				continue;
			}
		}
		break;
	}
}