#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_3__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_18__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_16__ {scalar_t__ listen; int /*<<< orphan*/  host; int /*<<< orphan*/  numerichost; int /*<<< orphan*/  tcp; scalar_t__ verify; scalar_t__ key_file; scalar_t__ cert_file; scalar_t__ ca_file; } ;
struct TYPE_17__ {int /*<<< orphan*/  ssl; int /*<<< orphan*/ * url_bio_method; int /*<<< orphan*/  ctx; TYPE_2__ tls_shared; } ;
typedef  TYPE_2__ TLSShared ;
typedef  TYPE_3__ TLSContext ;
typedef  TYPE_4__ BIO ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  BIO_TYPE_SOURCE_SINK ; 
 int /*<<< orphan*/ * BIO_meth_new (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BIO_meth_set_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_puts (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_meth_set_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__* BIO_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_data (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ERR_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_get_error () ; 
 int /*<<< orphan*/  SSL_CTX_load_verify_locations (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_options (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SSL_CTX_set_verify (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_use_PrivateKey_file (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_use_certificate_chain_file (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SSL_FILETYPE_PEM ; 
 int SSL_OP_NO_SSLv2 ; 
 int SSL_OP_NO_SSLv3 ; 
 int SSL_VERIFY_FAIL_IF_NO_PEER_CERT ; 
 int SSL_VERIFY_PEER ; 
 int SSL_accept (int /*<<< orphan*/ ) ; 
 int SSL_connect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_bio (int /*<<< orphan*/ ,TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  SSL_set_tlsext_host_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSLv23_client_method () ; 
 int /*<<< orphan*/  SSLv23_server_method () ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 int ff_openssl_init () ; 
 int ff_tls_open_underlying (TYPE_2__*,TYPE_1__*,char const*,int /*<<< orphan*/ **) ; 
 int print_tls_error (TYPE_1__*,int) ; 
 int /*<<< orphan*/  tls_close (TYPE_1__*) ; 
 int /*<<< orphan*/  url_bio_bputs ; 
 int /*<<< orphan*/  url_bio_bread ; 
 int /*<<< orphan*/  url_bio_bwrite ; 
 int /*<<< orphan*/  url_bio_create ; 
 int /*<<< orphan*/  url_bio_ctrl ; 
 int /*<<< orphan*/  url_bio_destroy ; 
 int /*<<< orphan*/  url_bio_method ; 

__attribute__((used)) static int tls_open(URLContext *h, const char *uri, int flags, AVDictionary **options)
{
    TLSContext *p = h->priv_data;
    TLSShared *c = &p->tls_shared;
    BIO *bio;
    int ret;

    if ((ret = ff_openssl_init()) < 0)
        return ret;

    if ((ret = ff_tls_open_underlying(c, h, uri, options)) < 0)
        goto fail;

    // We want to support all versions of TLS >= 1.0, but not the deprecated
    // and insecure SSLv2 and SSLv3.  Despite the name, SSLv23_*_method()
    // enables support for all versions of SSL and TLS, and we then disable
    // support for the old protocols immediately after creating the context.
    p->ctx = SSL_CTX_new(c->listen ? SSLv23_server_method() : SSLv23_client_method());
    if (!p->ctx) {
        av_log(h, AV_LOG_ERROR, "%s\n", ERR_error_string(ERR_get_error(), NULL));
        ret = AVERROR(EIO);
        goto fail;
    }
    SSL_CTX_set_options(p->ctx, SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3);
    if (c->ca_file) {
        if (!SSL_CTX_load_verify_locations(p->ctx, c->ca_file, NULL))
            av_log(h, AV_LOG_ERROR, "SSL_CTX_load_verify_locations %s\n", ERR_error_string(ERR_get_error(), NULL));
    }
    if (c->cert_file && !SSL_CTX_use_certificate_chain_file(p->ctx, c->cert_file)) {
        av_log(h, AV_LOG_ERROR, "Unable to load cert file %s: %s\n",
               c->cert_file, ERR_error_string(ERR_get_error(), NULL));
        ret = AVERROR(EIO);
        goto fail;
    }
    if (c->key_file && !SSL_CTX_use_PrivateKey_file(p->ctx, c->key_file, SSL_FILETYPE_PEM)) {
        av_log(h, AV_LOG_ERROR, "Unable to load key file %s: %s\n",
               c->key_file, ERR_error_string(ERR_get_error(), NULL));
        ret = AVERROR(EIO);
        goto fail;
    }
    // Note, this doesn't check that the peer certificate actually matches
    // the requested hostname.
    if (c->verify)
        SSL_CTX_set_verify(p->ctx, SSL_VERIFY_PEER|SSL_VERIFY_FAIL_IF_NO_PEER_CERT, NULL);
    p->ssl = SSL_new(p->ctx);
    if (!p->ssl) {
        av_log(h, AV_LOG_ERROR, "%s\n", ERR_error_string(ERR_get_error(), NULL));
        ret = AVERROR(EIO);
        goto fail;
    }
#if OPENSSL_VERSION_NUMBER >= 0x1010000fL
    p->url_bio_method = BIO_meth_new(BIO_TYPE_SOURCE_SINK, "urlprotocol bio");
    BIO_meth_set_write(p->url_bio_method, url_bio_bwrite);
    BIO_meth_set_read(p->url_bio_method, url_bio_bread);
    BIO_meth_set_puts(p->url_bio_method, url_bio_bputs);
    BIO_meth_set_ctrl(p->url_bio_method, url_bio_ctrl);
    BIO_meth_set_create(p->url_bio_method, url_bio_create);
    BIO_meth_set_destroy(p->url_bio_method, url_bio_destroy);
    bio = BIO_new(p->url_bio_method);
    BIO_set_data(bio, c->tcp);
#else
    bio = BIO_new(&url_bio_method);
    bio->ptr = c->tcp;
#endif
    SSL_set_bio(p->ssl, bio, bio);
    if (!c->listen && !c->numerichost)
        SSL_set_tlsext_host_name(p->ssl, c->host);
    ret = c->listen ? SSL_accept(p->ssl) : SSL_connect(p->ssl);
    if (ret == 0) {
        av_log(h, AV_LOG_ERROR, "Unable to negotiate TLS/SSL session\n");
        ret = AVERROR(EIO);
        goto fail;
    } else if (ret < 0) {
        ret = print_tls_error(h, ret);
        goto fail;
    }

    return 0;
fail:
    tls_close(h);
    return ret;
}