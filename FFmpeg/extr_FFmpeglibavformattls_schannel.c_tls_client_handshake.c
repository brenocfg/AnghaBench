#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_13__ {int cbBuffer; int /*<<< orphan*/  pvBuffer; } ;
struct TYPE_11__ {int /*<<< orphan*/  tcp; int /*<<< orphan*/  host; } ;
struct TYPE_12__ {int request_flags; int /*<<< orphan*/  ctxt_handle; int /*<<< orphan*/  ctxt_timestamp; int /*<<< orphan*/  context_flags; int /*<<< orphan*/  cred_handle; TYPE_2__ tls_shared; } ;
typedef  TYPE_2__ TLSShared ;
typedef  TYPE_3__ TLSContext ;
typedef  int /*<<< orphan*/  SecBufferDesc ;
typedef  TYPE_4__ SecBuffer ;
typedef  scalar_t__ SECURITY_STATUS ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_UNKNOWN ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  DeleteSecurityContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  FreeContextBuffer (int /*<<< orphan*/ ) ; 
 int ISC_REQ_ALLOCATE_MEMORY ; 
 int ISC_REQ_CONFIDENTIALITY ; 
 int ISC_REQ_REPLAY_DETECT ; 
 int ISC_REQ_SEQUENCE_DETECT ; 
 int ISC_REQ_STREAM ; 
 scalar_t__ InitializeSecurityContext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SECBUFFER_EMPTY ; 
 scalar_t__ SEC_I_CONTINUE_NEEDED ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 int ffurl_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_sec_buffer (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_sec_buffer_desc (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int tls_client_handshake_loop (TYPE_1__*,int) ; 

__attribute__((used)) static int tls_client_handshake(URLContext *h)
{
    TLSContext *c = h->priv_data;
    TLSShared *s = &c->tls_shared;
    SecBuffer outbuf;
    SecBufferDesc outbuf_desc;
    SECURITY_STATUS sspi_ret;
    int ret;

    init_sec_buffer(&outbuf, SECBUFFER_EMPTY, NULL, 0);
    init_sec_buffer_desc(&outbuf_desc, &outbuf, 1);

    c->request_flags = ISC_REQ_SEQUENCE_DETECT | ISC_REQ_REPLAY_DETECT |
                       ISC_REQ_CONFIDENTIALITY | ISC_REQ_ALLOCATE_MEMORY |
                       ISC_REQ_STREAM;

    sspi_ret = InitializeSecurityContext(&c->cred_handle, NULL, s->host, c->request_flags, 0, 0,
                                         NULL, 0, &c->ctxt_handle, &outbuf_desc, &c->context_flags,
                                         &c->ctxt_timestamp);
    if (sspi_ret != SEC_I_CONTINUE_NEEDED) {
        av_log(h, AV_LOG_ERROR, "Unable to create initial security context (0x%lx)\n", sspi_ret);
        ret = AVERROR_UNKNOWN;
        goto fail;
    }

    ret = ffurl_write(s->tcp, outbuf.pvBuffer, outbuf.cbBuffer);
    FreeContextBuffer(outbuf.pvBuffer);
    if (ret < 0 || ret != outbuf.cbBuffer) {
        av_log(h, AV_LOG_ERROR, "Failed to send initial handshake data\n");
        ret = AVERROR(EIO);
        goto fail;
    }

    return tls_client_handshake_loop(h, 1);

fail:
    DeleteSecurityContext(&c->ctxt_handle);
    return ret;
}