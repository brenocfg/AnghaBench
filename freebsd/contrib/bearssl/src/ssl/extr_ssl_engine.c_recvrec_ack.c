#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* vtable; } ;
struct TYPE_9__ {scalar_t__ iomode; unsigned char* ibuf; unsigned char* obuf; size_t ixb; size_t ixa; unsigned int ixc; unsigned char record_type_in; unsigned int version_in; int ibuf_len; TYPE_1__ in; scalar_t__ incrypt; } ;
typedef  TYPE_2__ br_ssl_engine_context ;
struct TYPE_10__ {unsigned char* (* decrypt ) (TYPE_3__**,unsigned char,unsigned int,unsigned char*,size_t*) ;int /*<<< orphan*/  (* check_length ) (TYPE_3__**,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BR_ERR_BAD_LENGTH ; 
 int /*<<< orphan*/  BR_ERR_BAD_MAC ; 
 int /*<<< orphan*/  BR_ERR_BAD_VERSION ; 
 int /*<<< orphan*/  BR_ERR_TOO_LARGE ; 
 int /*<<< orphan*/  BR_ERR_UNSUPPORTED_VERSION ; 
 scalar_t__ BR_IO_IN ; 
 scalar_t__ BR_IO_INOUT ; 
 unsigned int br_dec16be (unsigned char*) ; 
 int /*<<< orphan*/  br_ssl_engine_fail (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_ready_in (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__**,unsigned int) ; 
 unsigned char* stub2 (TYPE_3__**,unsigned char,unsigned int,unsigned char*,size_t*) ; 

__attribute__((used)) static void
recvrec_ack(br_ssl_engine_context *rc, size_t len)
{
	unsigned char *pbuf;
	size_t pbuf_len;

	/*
	 * Adjust state if necessary (for a shared input/output buffer):
	 * we got some incoming bytes, so we cannot (temporarily) handle
	 * outgoing data.
	 */
	if (rc->iomode == BR_IO_INOUT && rc->ibuf == rc->obuf) {
		rc->iomode = BR_IO_IN;
	}

	/*
	 * Adjust data pointers.
	 */
	rc->ixb = (rc->ixa += len);
	rc->ixc -= len;

	/*
	 * If we are receiving a header and did not fully obtained it
	 * yet, then just wait for the next bytes.
	 */
	if (rc->ixa < 5) {
		return;
	}

	/*
	 * If we just obtained a full header, process it.
	 */
	if (rc->ixa == 5) {
		unsigned version;
		unsigned rlen;

		/*
		 * Get record type and version. We support only versions
		 * 3.x (if the version major number does not match, then
		 * we suppose that the record format is too alien for us
		 * to process it).
		 *
		 * Note: right now, we reject clients that try to send
		 * a ClientHello in a format compatible with SSL-2.0. It
		 * is unclear whether this will ever be supported; and
		 * if we want to support it, then this might be done in
		 * in the server-specific code, not here.
		 */
		rc->record_type_in = rc->ibuf[0];
		version = br_dec16be(rc->ibuf + 1);
		if ((version >> 8) != 3) {
			br_ssl_engine_fail(rc, BR_ERR_UNSUPPORTED_VERSION);
			return;
		}

		/*
		 * We ensure that successive records have the same
		 * version. The handshake code must check and adjust the
		 * variables when necessary to accommodate the protocol
		 * negotiation details.
		 */
		if (rc->version_in != 0 && rc->version_in != version) {
			br_ssl_engine_fail(rc, BR_ERR_BAD_VERSION);
			return;
		}
		rc->version_in = version;

		/*
		 * Decode record length. We must check that the length
		 * is valid (relatively to the current encryption mode)
		 * and also (if encryption is active) that the record
		 * will fit in our buffer.
		 *
		 * When no encryption is active, we can process records
		 * by chunks, and thus accept any record up to the
		 * maximum allowed plaintext length (16384 bytes).
		 */
		rlen = br_dec16be(rc->ibuf + 3);
		if (rc->incrypt) {
			if (!rc->in.vtable->check_length(
				&rc->in.vtable, rlen))
			{
				br_ssl_engine_fail(rc, BR_ERR_BAD_LENGTH);
				return;
			}
			if (rlen > (rc->ibuf_len - 5)) {
				br_ssl_engine_fail(rc, BR_ERR_TOO_LARGE);
				return;
			}
		} else {
			if (rlen > 16384) {
				br_ssl_engine_fail(rc, BR_ERR_BAD_LENGTH);
				return;
			}
		}

		/*
		 * If the record is completely empty then we must switch
		 * to a new record. Note that, in that case, we
		 * completely ignore the record type, which is fitting
		 * since we received no actual data of that type.
		 *
		 * A completely empty record is technically allowed as
		 * long as encryption/MAC is not active, i.e. before
		 * completion of the first handshake. It it still weird;
		 * it might conceptually be useful as a heartbeat or
		 * keep-alive mechanism while some lengthy operation is
		 * going on, e.g. interaction with a human user.
		 */
		if (rlen == 0) {
			make_ready_in(rc);
		} else {
			rc->ixa = rc->ixb = 5;
			rc->ixc = rlen;
		}
		return;
	}

	/*
	 * If there is no active encryption, then the data can be read
	 * right away. Note that we do not receive bytes from the
	 * transport medium when we still have payload bytes to be
	 * acknowledged.
	 */
	if (!rc->incrypt) {
		rc->ixa = 5;
		return;
	}

	/*
	 * Since encryption is active, we must wait for a full record
	 * before processing it.
	 */
	if (rc->ixc != 0) {
		return;
	}

	/*
	 * We got the full record. Decrypt it.
	 */
	pbuf_len = rc->ixa - 5;
	pbuf = rc->in.vtable->decrypt(&rc->in.vtable,
		rc->record_type_in, rc->version_in, rc->ibuf + 5, &pbuf_len);
	if (pbuf == 0) {
		br_ssl_engine_fail(rc, BR_ERR_BAD_MAC);
		return;
	}
	rc->ixa = (size_t)(pbuf - rc->ibuf);
	rc->ixb = rc->ixa + pbuf_len;

	/*
	 * Decryption may have yielded an empty record, in which case
	 * we get back to "ready" state immediately.
	 */
	if (rc->ixa == rc->ixb) {
		make_ready_in(rc);
	}
}