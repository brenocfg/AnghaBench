#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gnutls_x509_crt_t ;
typedef  int /*<<< orphan*/  gnutls_datum_t ;
struct TYPE_10__ {TYPE_3__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_11__ {int /*<<< orphan*/  host; scalar_t__ verify; int /*<<< orphan*/  tcp; scalar_t__ key_file; scalar_t__ cert_file; scalar_t__ ca_file; int /*<<< orphan*/  numerichost; scalar_t__ listen; } ;
struct TYPE_12__ {int need_shutdown; int /*<<< orphan*/  session; int /*<<< orphan*/  cred; TYPE_2__ tls_shared; } ;
typedef  TYPE_2__ TLSShared ;
typedef  TYPE_3__ TLSContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EIO ; 
 unsigned int GNUTLS_CERT_INVALID ; 
 int /*<<< orphan*/  GNUTLS_CLIENT ; 
 int /*<<< orphan*/  GNUTLS_CRD_CERTIFICATE ; 
 scalar_t__ GNUTLS_CRT_X509 ; 
 int /*<<< orphan*/  GNUTLS_NAME_DNS ; 
 int /*<<< orphan*/  GNUTLS_SERVER ; 
 int /*<<< orphan*/  GNUTLS_VERIFY_ALLOW_X509_V1_CA_CRT ; 
 int /*<<< orphan*/  GNUTLS_X509_FMT_DER ; 
 int /*<<< orphan*/  GNUTLS_X509_FMT_PEM ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ff_gnutls_init () ; 
 int ff_tls_open_underlying (TYPE_2__*,TYPE_1__*,char const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  gnutls_certificate_allocate_credentials (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gnutls_certificate_get_peers (int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  gnutls_certificate_set_verify_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gnutls_certificate_set_x509_key_file (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_certificate_set_x509_system_trust (int /*<<< orphan*/ ) ; 
 int gnutls_certificate_set_x509_trust_file (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ gnutls_certificate_type_get (int /*<<< orphan*/ ) ; 
 int gnutls_certificate_verify_peers2 (int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  gnutls_credentials_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gnutls_error_is_fatal (int) ; 
 int gnutls_handshake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_priority_set_direct (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gnutls_server_name_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_strerror (int) ; 
 int /*<<< orphan*/  gnutls_transport_set_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_transport_set_pull_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_transport_set_push_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_url_pull ; 
 int /*<<< orphan*/  gnutls_url_push ; 
 int gnutls_x509_crt_check_hostname (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_x509_crt_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_x509_crt_import (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_x509_crt_init (int /*<<< orphan*/ *) ; 
 int print_tls_error (TYPE_1__*,int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_close (TYPE_1__*) ; 

__attribute__((used)) static int tls_open(URLContext *h, const char *uri, int flags, AVDictionary **options)
{
    TLSContext *p = h->priv_data;
    TLSShared *c = &p->tls_shared;
    int ret;

    ff_gnutls_init();

    if ((ret = ff_tls_open_underlying(c, h, uri, options)) < 0)
        goto fail;

    gnutls_init(&p->session, c->listen ? GNUTLS_SERVER : GNUTLS_CLIENT);
    if (!c->listen && !c->numerichost)
        gnutls_server_name_set(p->session, GNUTLS_NAME_DNS, c->host, strlen(c->host));
    gnutls_certificate_allocate_credentials(&p->cred);
    if (c->ca_file) {
        ret = gnutls_certificate_set_x509_trust_file(p->cred, c->ca_file, GNUTLS_X509_FMT_PEM);
        if (ret < 0)
            av_log(h, AV_LOG_ERROR, "%s\n", gnutls_strerror(ret));
    }
#if GNUTLS_VERSION_NUMBER >= 0x030020
    else
        gnutls_certificate_set_x509_system_trust(p->cred);
#endif
    gnutls_certificate_set_verify_flags(p->cred, c->verify ?
                                        GNUTLS_VERIFY_ALLOW_X509_V1_CA_CRT : 0);
    if (c->cert_file && c->key_file) {
        ret = gnutls_certificate_set_x509_key_file(p->cred,
                                                   c->cert_file, c->key_file,
                                                   GNUTLS_X509_FMT_PEM);
        if (ret < 0) {
            av_log(h, AV_LOG_ERROR,
                   "Unable to set cert/key files %s and %s: %s\n",
                   c->cert_file, c->key_file, gnutls_strerror(ret));
            ret = AVERROR(EIO);
            goto fail;
        }
    } else if (c->cert_file || c->key_file)
        av_log(h, AV_LOG_ERROR, "cert and key required\n");
    gnutls_credentials_set(p->session, GNUTLS_CRD_CERTIFICATE, p->cred);
    gnutls_transport_set_pull_function(p->session, gnutls_url_pull);
    gnutls_transport_set_push_function(p->session, gnutls_url_push);
    gnutls_transport_set_ptr(p->session, c->tcp);
    gnutls_priority_set_direct(p->session, "NORMAL", NULL);
    do {
        ret = gnutls_handshake(p->session);
        if (gnutls_error_is_fatal(ret)) {
            ret = print_tls_error(h, ret);
            goto fail;
        }
    } while (ret);
    p->need_shutdown = 1;
    if (c->verify) {
        unsigned int status, cert_list_size;
        gnutls_x509_crt_t cert;
        const gnutls_datum_t *cert_list;
        if ((ret = gnutls_certificate_verify_peers2(p->session, &status)) < 0) {
            av_log(h, AV_LOG_ERROR, "Unable to verify peer certificate: %s\n",
                                    gnutls_strerror(ret));
            ret = AVERROR(EIO);
            goto fail;
        }
        if (status & GNUTLS_CERT_INVALID) {
            av_log(h, AV_LOG_ERROR, "Peer certificate failed verification\n");
            ret = AVERROR(EIO);
            goto fail;
        }
        if (gnutls_certificate_type_get(p->session) != GNUTLS_CRT_X509) {
            av_log(h, AV_LOG_ERROR, "Unsupported certificate type\n");
            ret = AVERROR(EIO);
            goto fail;
        }
        gnutls_x509_crt_init(&cert);
        cert_list = gnutls_certificate_get_peers(p->session, &cert_list_size);
        gnutls_x509_crt_import(cert, cert_list, GNUTLS_X509_FMT_DER);
        ret = gnutls_x509_crt_check_hostname(cert, c->host);
        gnutls_x509_crt_deinit(cert);
        if (!ret) {
            av_log(h, AV_LOG_ERROR,
                   "The certificate's owner does not match hostname %s\n", c->host);
            ret = AVERROR(EIO);
            goto fail;
        }
    }

    return 0;
fail:
    tls_close(h);
    return ret;
}