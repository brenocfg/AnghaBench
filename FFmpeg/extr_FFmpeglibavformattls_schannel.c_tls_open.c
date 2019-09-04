#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_3__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_15__ {int dwFlags; int /*<<< orphan*/  dwVersion; int /*<<< orphan*/  member_0; } ;
struct TYPE_13__ {scalar_t__ verify; scalar_t__ listen; } ;
struct TYPE_14__ {int connected; int /*<<< orphan*/  cred_timestamp; int /*<<< orphan*/  cred_handle; TYPE_2__ tls_shared; } ;
typedef  TYPE_2__ TLSShared ;
typedef  TYPE_3__ TLSContext ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  scalar_t__ SECURITY_STATUS ;
typedef  TYPE_4__ SCHANNEL_CRED ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_UNKNOWN ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AcquireCredentialsHandle (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SCHANNEL_CRED_VERSION ; 
 int SCH_CRED_AUTO_CRED_VALIDATION ; 
 int SCH_CRED_IGNORE_NO_REVOCATION_CHECK ; 
 int SCH_CRED_IGNORE_REVOCATION_OFFLINE ; 
 int SCH_CRED_MANUAL_CRED_VALIDATION ; 
 int SCH_CRED_REVOCATION_CHECK_CHAIN ; 
 int /*<<< orphan*/  SECPKG_CRED_OUTBOUND ; 
 scalar_t__ SEC_E_OK ; 
 scalar_t__ UNISP_NAME ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 int ff_tls_open_underlying (TYPE_2__*,TYPE_1__*,char const*,int /*<<< orphan*/ **) ; 
 int tls_client_handshake (TYPE_1__*) ; 
 int /*<<< orphan*/  tls_close (TYPE_1__*) ; 

__attribute__((used)) static int tls_open(URLContext *h, const char *uri, int flags, AVDictionary **options)
{
    TLSContext *c = h->priv_data;
    TLSShared *s = &c->tls_shared;
    SECURITY_STATUS sspi_ret;
    SCHANNEL_CRED schannel_cred = { 0 };
    int ret;

    if ((ret = ff_tls_open_underlying(s, h, uri, options)) < 0)
        goto fail;

    if (s->listen) {
        av_log(h, AV_LOG_ERROR, "TLS Listen Sockets with SChannel is not implemented.\n");
        ret = AVERROR(EINVAL);
        goto fail;
    }

    /* SChannel Options */
    schannel_cred.dwVersion = SCHANNEL_CRED_VERSION;

    if (s->verify)
        schannel_cred.dwFlags = SCH_CRED_AUTO_CRED_VALIDATION |
                                SCH_CRED_REVOCATION_CHECK_CHAIN;
    else
        schannel_cred.dwFlags = SCH_CRED_MANUAL_CRED_VALIDATION |
                                SCH_CRED_IGNORE_NO_REVOCATION_CHECK |
                                SCH_CRED_IGNORE_REVOCATION_OFFLINE;

    /* Get credential handle */
    sspi_ret = AcquireCredentialsHandle(NULL, (TCHAR *)UNISP_NAME, SECPKG_CRED_OUTBOUND,
                                        NULL,  &schannel_cred, NULL, NULL, &c->cred_handle,
                                        &c->cred_timestamp);
    if (sspi_ret != SEC_E_OK) {
        av_log(h, AV_LOG_ERROR, "Unable to acquire security credentials (0x%lx)\n", sspi_ret);
        ret = AVERROR_UNKNOWN;
        goto fail;
    }

    ret = tls_client_handshake(h);
    if (ret < 0)
        goto fail;

    c->connected = 1;

    return 0;

fail:
    tls_close(h);
    return ret;
}