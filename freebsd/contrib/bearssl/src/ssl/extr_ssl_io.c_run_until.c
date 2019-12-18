#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int (* low_write ) (int /*<<< orphan*/ ,unsigned char*,size_t) ;int (* low_read ) (int /*<<< orphan*/ ,unsigned char*,size_t) ;TYPE_3__* engine; int /*<<< orphan*/  read_context; int /*<<< orphan*/  write_context; } ;
typedef  TYPE_1__ br_sslio_context ;
struct TYPE_11__ {int /*<<< orphan*/  shutdown_recv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BR_ERR_IO ; 
 unsigned int BR_SSL_CLOSED ; 
 unsigned int BR_SSL_RECVAPP ; 
 unsigned int BR_SSL_RECVREC ; 
 unsigned int BR_SSL_SENDREC ; 
 unsigned int br_ssl_engine_current_state (TYPE_3__*) ; 
 int /*<<< orphan*/  br_ssl_engine_fail (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_ssl_engine_flush (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_ssl_engine_recvrec_ack (TYPE_3__*,int) ; 
 unsigned char* br_ssl_engine_recvrec_buf (TYPE_3__*,size_t*) ; 
 int /*<<< orphan*/  br_ssl_engine_sendrec_ack (TYPE_3__*,int) ; 
 unsigned char* br_ssl_engine_sendrec_buf (TYPE_3__*,size_t*) ; 
 int stub1 (int /*<<< orphan*/ ,unsigned char*,size_t) ; 
 int stub2 (int /*<<< orphan*/ ,unsigned char*,size_t) ; 

__attribute__((used)) static int
run_until(br_sslio_context *ctx, unsigned target)
{
	for (;;) {
		unsigned state;

		state = br_ssl_engine_current_state(ctx->engine);
		if (state & BR_SSL_CLOSED) {
			return -1;
		}

		/*
		 * If there is some record data to send, do it. This takes
		 * precedence over everything else.
		 */
		if (state & BR_SSL_SENDREC) {
			unsigned char *buf;
			size_t len;
			int wlen;

			buf = br_ssl_engine_sendrec_buf(ctx->engine, &len);
			wlen = ctx->low_write(ctx->write_context, buf, len);
			if (wlen < 0) {
				/*
				 * If we received a close_notify and we
				 * still send something, then we have our
				 * own response close_notify to send, and
				 * the peer is allowed by RFC 5246 not to
				 * wait for it.
				 */
				if (!ctx->engine->shutdown_recv) {
					br_ssl_engine_fail(
						ctx->engine, BR_ERR_IO);
				}
				return -1;
			}
			if (wlen > 0) {
				br_ssl_engine_sendrec_ack(ctx->engine, wlen);
			}
			continue;
		}

		/*
		 * If we reached our target, then we are finished.
		 */
		if (state & target) {
			return 0;
		}

		/*
		 * If some application data must be read, and we did not
		 * exit, then this means that we are trying to write data,
		 * and that's not possible until the application data is
		 * read. This may happen if using a shared in/out buffer,
		 * and the underlying protocol is not strictly half-duplex.
		 * This is unrecoverable here, so we report an error.
		 */
		if (state & BR_SSL_RECVAPP) {
			return -1;
		}

		/*
		 * If we reached that point, then either we are trying
		 * to read data and there is some, or the engine is stuck
		 * until a new record is obtained.
		 */
		if (state & BR_SSL_RECVREC) {
			unsigned char *buf;
			size_t len;
			int rlen;

			buf = br_ssl_engine_recvrec_buf(ctx->engine, &len);
			rlen = ctx->low_read(ctx->read_context, buf, len);
			if (rlen < 0) {
				br_ssl_engine_fail(ctx->engine, BR_ERR_IO);
				return -1;
			}
			if (rlen > 0) {
				br_ssl_engine_recvrec_ack(ctx->engine, rlen);
			}
			continue;
		}

		/*
		 * We can reach that point if the target RECVAPP, and
		 * the state contains SENDAPP only. This may happen with
		 * a shared in/out buffer. In that case, we must flush
		 * the buffered data to "make room" for a new incoming
		 * record.
		 */
		br_ssl_engine_flush(ctx->engine, 0);
	}
}