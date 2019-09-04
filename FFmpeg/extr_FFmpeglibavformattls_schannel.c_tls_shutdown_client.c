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
typedef  int /*<<< orphan*/  dwshut ;
struct TYPE_9__ {TYPE_3__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_12__ {int cbBuffer; int /*<<< orphan*/  pvBuffer; } ;
struct TYPE_10__ {int /*<<< orphan*/  tcp; int /*<<< orphan*/  host; } ;
struct TYPE_11__ {scalar_t__ connected; int /*<<< orphan*/  ctxt_timestamp; int /*<<< orphan*/  context_flags; int /*<<< orphan*/  ctxt_handle; int /*<<< orphan*/  request_flags; int /*<<< orphan*/  cred_handle; TYPE_2__ tls_shared; } ;
typedef  TYPE_2__ TLSShared ;
typedef  TYPE_3__ TLSContext ;
typedef  int /*<<< orphan*/  SecBufferDesc ;
typedef  TYPE_4__ SecBuffer ;
typedef  scalar_t__ SECURITY_STATUS ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ ApplyControlToken (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeContextBuffer (int /*<<< orphan*/ ) ; 
 scalar_t__ InitializeSecurityContext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCHANNEL_SHUTDOWN ; 
 int /*<<< orphan*/  SECBUFFER_EMPTY ; 
 int /*<<< orphan*/  SECBUFFER_TOKEN ; 
 scalar_t__ SEC_E_OK ; 
 scalar_t__ SEC_I_CONTEXT_EXPIRED ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int ffurl_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_sec_buffer (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_sec_buffer_desc (int /*<<< orphan*/ *,TYPE_4__*,int) ; 

__attribute__((used)) static int tls_shutdown_client(URLContext *h)
{
    TLSContext *c = h->priv_data;
    TLSShared *s = &c->tls_shared;
    int ret;

    if (c->connected) {
        SecBufferDesc BuffDesc;
        SecBuffer Buffer;
        SECURITY_STATUS sspi_ret;
        SecBuffer outbuf;
        SecBufferDesc outbuf_desc;

        DWORD dwshut = SCHANNEL_SHUTDOWN;
        init_sec_buffer(&Buffer, SECBUFFER_TOKEN, &dwshut, sizeof(dwshut));
        init_sec_buffer_desc(&BuffDesc, &Buffer, 1);

        sspi_ret = ApplyControlToken(&c->ctxt_handle, &BuffDesc);
        if (sspi_ret != SEC_E_OK)
            av_log(h, AV_LOG_ERROR, "ApplyControlToken failed\n");

        init_sec_buffer(&outbuf, SECBUFFER_EMPTY, NULL, 0);
        init_sec_buffer_desc(&outbuf_desc, &outbuf, 1);

        sspi_ret = InitializeSecurityContext(&c->cred_handle, &c->ctxt_handle, s->host,
                                             c->request_flags, 0, 0, NULL, 0, &c->ctxt_handle,
                                             &outbuf_desc, &c->context_flags, &c->ctxt_timestamp);
        if (sspi_ret == SEC_E_OK || sspi_ret == SEC_I_CONTEXT_EXPIRED) {
            ret = ffurl_write(s->tcp, outbuf.pvBuffer, outbuf.cbBuffer);
            FreeContextBuffer(outbuf.pvBuffer);
            if (ret < 0 || ret != outbuf.cbBuffer)
                av_log(h, AV_LOG_ERROR, "Failed to send close message\n");
        }

        c->connected = 0;
    }
    return 0;
}