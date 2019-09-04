#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_12__ {scalar_t__ BufferType; int cbBuffer; int /*<<< orphan*/ * pvBuffer; } ;
struct TYPE_10__ {int /*<<< orphan*/  tcp; int /*<<< orphan*/  host; } ;
struct TYPE_11__ {scalar_t__ enc_buf_offset; scalar_t__ enc_buf_size; int request_flags; int /*<<< orphan*/ * enc_buf; TYPE_2__ tls_shared; int /*<<< orphan*/  ctxt_timestamp; int /*<<< orphan*/  context_flags; int /*<<< orphan*/  ctxt_handle; int /*<<< orphan*/  cred_handle; void* dec_buf_size; int /*<<< orphan*/ * dec_buf; scalar_t__ dec_buf_offset; } ;
typedef  TYPE_2__ TLSShared ;
typedef  TYPE_3__ TLSContext ;
typedef  int /*<<< orphan*/  SecBufferDesc ;
typedef  TYPE_4__ SecBuffer ;
typedef  scalar_t__ SECURITY_STATUS ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_UNKNOWN ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FreeContextBuffer (int /*<<< orphan*/ *) ; 
 int ISC_REQ_USE_SUPPLIED_CREDS ; 
 scalar_t__ InitializeSecurityContext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SCHANNEL_FREE_BUFFER_SIZE ; 
 void* SCHANNEL_INITIAL_BUFFER_SIZE ; 
 scalar_t__ SECBUFFER_ALERT ; 
 scalar_t__ SECBUFFER_EMPTY ; 
 scalar_t__ SECBUFFER_EXTRA ; 
 scalar_t__ SECBUFFER_TOKEN ; 
 scalar_t__ SEC_E_INCOMPLETE_MESSAGE ; 
 scalar_t__ SEC_E_OK ; 
 scalar_t__ SEC_E_WRONG_PRINCIPAL ; 
 scalar_t__ SEC_I_CONTINUE_NEEDED ; 
 scalar_t__ SEC_I_INCOMPLETE_CREDENTIALS ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * av_malloc (int) ; 
 int av_reallocp (int /*<<< orphan*/ **,void*) ; 
 int ffurl_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int ffurl_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_sec_buffer (TYPE_4__*,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_sec_buffer_desc (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int tls_client_handshake_loop(URLContext *h, int initial)
{
    TLSContext *c = h->priv_data;
    TLSShared *s = &c->tls_shared;
    SECURITY_STATUS sspi_ret;
    SecBuffer outbuf[3] = { 0 };
    SecBufferDesc outbuf_desc;
    SecBuffer inbuf[2];
    SecBufferDesc inbuf_desc;
    int i, ret = 0, read_data = initial;

    if (c->enc_buf == NULL) {
        c->enc_buf_offset = 0;
        ret = av_reallocp(&c->enc_buf, SCHANNEL_INITIAL_BUFFER_SIZE);
        if (ret < 0)
            goto fail;
        c->enc_buf_size = SCHANNEL_INITIAL_BUFFER_SIZE;
    }

    if (c->dec_buf == NULL) {
        c->dec_buf_offset = 0;
        ret = av_reallocp(&c->dec_buf, SCHANNEL_INITIAL_BUFFER_SIZE);
        if (ret < 0)
            goto fail;
        c->dec_buf_size = SCHANNEL_INITIAL_BUFFER_SIZE;
    }

    while (1) {
        if (c->enc_buf_size - c->enc_buf_offset < SCHANNEL_FREE_BUFFER_SIZE) {
            c->enc_buf_size = c->enc_buf_offset + SCHANNEL_FREE_BUFFER_SIZE;
            ret = av_reallocp(&c->enc_buf, c->enc_buf_size);
            if (ret < 0) {
                c->enc_buf_size = c->enc_buf_offset = 0;
                goto fail;
            }
        }

        if (read_data) {
            ret = ffurl_read(c->tls_shared.tcp, c->enc_buf + c->enc_buf_offset,
                             c->enc_buf_size - c->enc_buf_offset);
            if (ret < 0) {
                av_log(h, AV_LOG_ERROR, "Failed to read handshake response\n");
                goto fail;
            }
            c->enc_buf_offset += ret;
        }

        /* input buffers */
        init_sec_buffer(&inbuf[0], SECBUFFER_TOKEN, av_malloc(c->enc_buf_offset), c->enc_buf_offset);
        init_sec_buffer(&inbuf[1], SECBUFFER_EMPTY, NULL, 0);
        init_sec_buffer_desc(&inbuf_desc, inbuf, 2);

        if (inbuf[0].pvBuffer == NULL) {
            av_log(h, AV_LOG_ERROR, "Failed to allocate input buffer\n");
            ret = AVERROR(ENOMEM);
            goto fail;
        }

        memcpy(inbuf[0].pvBuffer, c->enc_buf, c->enc_buf_offset);

        /* output buffers */
        init_sec_buffer(&outbuf[0], SECBUFFER_TOKEN, NULL, 0);
        init_sec_buffer(&outbuf[1], SECBUFFER_ALERT, NULL, 0);
        init_sec_buffer(&outbuf[2], SECBUFFER_EMPTY, NULL, 0);
        init_sec_buffer_desc(&outbuf_desc, outbuf, 3);

        sspi_ret = InitializeSecurityContext(&c->cred_handle, &c->ctxt_handle, s->host, c->request_flags,
                                             0, 0, &inbuf_desc, 0, NULL, &outbuf_desc, &c->context_flags,
                                             &c->ctxt_timestamp);
        av_freep(&inbuf[0].pvBuffer);

        if (sspi_ret == SEC_E_INCOMPLETE_MESSAGE) {
            av_log(h, AV_LOG_DEBUG, "Received incomplete handshake, need more data\n");
            read_data = 1;
            continue;
        }

        /* remote requests a client certificate - attempt to continue without one anyway */
        if (sspi_ret == SEC_I_INCOMPLETE_CREDENTIALS &&
            !(c->request_flags & ISC_REQ_USE_SUPPLIED_CREDS)) {
            av_log(h, AV_LOG_VERBOSE, "Client certificate has been requested, ignoring\n");
            c->request_flags |= ISC_REQ_USE_SUPPLIED_CREDS;
            read_data = 0;
            continue;
        }

        /* continue handshake */
        if (sspi_ret == SEC_I_CONTINUE_NEEDED || sspi_ret == SEC_E_OK) {
            for (i = 0; i < 3; i++) {
                if (outbuf[i].BufferType == SECBUFFER_TOKEN && outbuf[i].cbBuffer > 0) {
                    ret = ffurl_write(c->tls_shared.tcp, outbuf[i].pvBuffer, outbuf[i].cbBuffer);
                    if (ret < 0 || ret != outbuf[i].cbBuffer) {
                        av_log(h, AV_LOG_VERBOSE, "Failed to send handshake data\n");
                        ret = AVERROR(EIO);
                        goto fail;
                    }
                }

                if (outbuf[i].pvBuffer != NULL) {
                    FreeContextBuffer(outbuf[i].pvBuffer);
                    outbuf[i].pvBuffer = NULL;
                }
            }
        } else {
            if (sspi_ret == SEC_E_WRONG_PRINCIPAL)
                av_log(h, AV_LOG_ERROR, "SNI or certificate check failed\n");
            else
                av_log(h, AV_LOG_ERROR, "Creating security context failed (0x%lx)\n", sspi_ret);
            ret = AVERROR_UNKNOWN;
            goto fail;
        }

        if (inbuf[1].BufferType == SECBUFFER_EXTRA && inbuf[1].cbBuffer > 0) {
            if (c->enc_buf_offset > inbuf[1].cbBuffer) {
                memmove(c->enc_buf, (c->enc_buf + c->enc_buf_offset) - inbuf[1].cbBuffer,
                        inbuf[1].cbBuffer);
                c->enc_buf_offset = inbuf[1].cbBuffer;
                if (sspi_ret == SEC_I_CONTINUE_NEEDED) {
                    read_data = 0;
                    continue;
                }
            }
        } else {
            c->enc_buf_offset  = 0;
        }

        if (sspi_ret == SEC_I_CONTINUE_NEEDED) {
            read_data = 1;
            continue;
        }

        break;
    }

    return 0;

fail:
    /* free any remaining output data */
    for (i = 0; i < 3; i++) {
        if (outbuf[i].pvBuffer != NULL) {
            FreeContextBuffer(outbuf[i].pvBuffer);
            outbuf[i].pvBuffer = NULL;
        }
    }

    return ret;
}