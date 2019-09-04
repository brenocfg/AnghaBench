#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_3__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_13__ {int /*<<< orphan*/  verify; int /*<<< orphan*/  host; scalar_t__ cert_file; scalar_t__ ca_file; scalar_t__ listen; } ;
struct TYPE_14__ {int /*<<< orphan*/  ca_array; int /*<<< orphan*/  ssl_context; TYPE_2__ tls_shared; } ;
typedef  TYPE_2__ TLSShared ;
typedef  TYPE_3__ TLSContext ;
typedef  scalar_t__ SecTrustResultType ;
typedef  scalar_t__ SecTrustRef ;
typedef  scalar_t__ OSStatus ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_UNKNOWN ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  CFRelease (scalar_t__) ; 
 int /*<<< orphan*/  CHECK_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,...) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ SSLCopyPeerTrust (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  SSLCreateContext (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SSLHandshake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSLSetConnection ; 
 int /*<<< orphan*/  SSLSetIOFuncs ; 
 int /*<<< orphan*/  SSLSetPeerDomainName ; 
 int /*<<< orphan*/  SSLSetSessionOption ; 
 scalar_t__ SecTrustEvaluate (scalar_t__,scalar_t__*) ; 
 scalar_t__ SecTrustSetAnchorCertificates (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ errSSLBadCert ; 
 scalar_t__ errSSLServerAuthCompleted ; 
 scalar_t__ errSSLWouldBlock ; 
 scalar_t__ errSSLXCertChainInvalid ; 
 int ff_tls_open_underlying (TYPE_2__*,TYPE_1__*,char const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  kSSLClientSide ; 
 int /*<<< orphan*/  kSSLServerSide ; 
 int /*<<< orphan*/  kSSLSessionOptionBreakOnServerAuth ; 
 int /*<<< orphan*/  kSSLStreamType ; 
 scalar_t__ kSecTrustResultProceed ; 
 scalar_t__ kSecTrustResultRecoverableTrustFailure ; 
 scalar_t__ kSecTrustResultUnspecified ; 
 int load_ca (TYPE_1__*) ; 
 int load_cert (TYPE_1__*) ; 
 scalar_t__ noErr ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_close (TYPE_1__*) ; 
 int /*<<< orphan*/  tls_read_cb ; 
 int /*<<< orphan*/  tls_write_cb ; 

__attribute__((used)) static int tls_open(URLContext *h, const char *uri, int flags, AVDictionary **options)
{
    TLSContext *c = h->priv_data;
    TLSShared *s = &c->tls_shared;
    int ret;

    if ((ret = ff_tls_open_underlying(s, h, uri, options)) < 0)
        goto fail;

    c->ssl_context = SSLCreateContext(NULL, s->listen ? kSSLServerSide : kSSLClientSide, kSSLStreamType);
    if (!c->ssl_context) {
        av_log(h, AV_LOG_ERROR, "Unable to create SSL context\n");
        ret = AVERROR(ENOMEM);
        goto fail;
    }
    if (s->ca_file) {
        if ((ret = load_ca(h)) < 0)
            goto fail;
    }
    if (s->ca_file || !s->verify)
        CHECK_ERROR(SSLSetSessionOption, c->ssl_context, kSSLSessionOptionBreakOnServerAuth, true);
    if (s->cert_file)
        if ((ret = load_cert(h)) < 0)
            goto fail;
    CHECK_ERROR(SSLSetPeerDomainName, c->ssl_context, s->host, strlen(s->host));
    CHECK_ERROR(SSLSetIOFuncs, c->ssl_context, tls_read_cb, tls_write_cb);
    CHECK_ERROR(SSLSetConnection, c->ssl_context, h);
    while (1) {
        OSStatus status = SSLHandshake(c->ssl_context);
        if (status == errSSLServerAuthCompleted) {
            SecTrustRef peerTrust;
            SecTrustResultType trustResult;
            if (!s->verify)
                continue;

            if (SSLCopyPeerTrust(c->ssl_context, &peerTrust) != noErr) {
                ret = AVERROR(ENOMEM);
                goto fail;
            }

            if (SecTrustSetAnchorCertificates(peerTrust, c->ca_array) != noErr) {
                ret = AVERROR_UNKNOWN;
                goto fail;
            }

            if (SecTrustEvaluate(peerTrust, &trustResult) != noErr) {
                ret = AVERROR_UNKNOWN;
                goto fail;
            }

            if (trustResult == kSecTrustResultProceed ||
                trustResult == kSecTrustResultUnspecified) {
                // certificate is trusted
                status = errSSLWouldBlock; // so we call SSLHandshake again
            } else if (trustResult == kSecTrustResultRecoverableTrustFailure) {
                // not trusted, for some reason other than being expired
                status = errSSLXCertChainInvalid;
            } else {
                // cannot use this certificate (fatal)
                status = errSSLBadCert;
            }

            if (peerTrust)
                CFRelease(peerTrust);
        }
        if (status == noErr) {
            break;
        } else if (status != errSSLWouldBlock) {
            av_log(h, AV_LOG_ERROR, "Unable to negotiate TLS/SSL session: %i\n", (int)status);
            ret = AVERROR(EIO);
            goto fail;
        }
    }

    return 0;
fail:
    tls_close(h);
    return ret;
}