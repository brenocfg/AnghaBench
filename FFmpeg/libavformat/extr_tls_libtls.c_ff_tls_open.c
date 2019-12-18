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
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct tls_config {int dummy; } ;
struct tls {int dummy; } ;
struct TYPE_9__ {TYPE_3__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_10__ {int /*<<< orphan*/  tcp; int /*<<< orphan*/  host; int /*<<< orphan*/  listen; int /*<<< orphan*/  verify; scalar_t__ key_file; scalar_t__ cert_file; scalar_t__ ca_file; } ;
struct TYPE_11__ {struct tls* ctx; TYPE_2__ tls_shared; } ;
typedef  TYPE_2__ TLSShared ;
typedef  TYPE_3__ TLSContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  TLS_PROTOCOLS_ALL ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_tls_close (TYPE_1__*) ; 
 int ff_tls_open_underlying (TYPE_2__*,TYPE_1__*,char const*,int /*<<< orphan*/ **) ; 
 int tls_accept_cbs (struct tls*,struct tls**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tls* tls_client () ; 
 int /*<<< orphan*/  tls_config_error (struct tls_config*) ; 
 int /*<<< orphan*/  tls_config_free (struct tls_config*) ; 
 int /*<<< orphan*/  tls_config_insecure_noverifycert (struct tls_config*) ; 
 int /*<<< orphan*/  tls_config_insecure_noverifyname (struct tls_config*) ; 
 int /*<<< orphan*/  tls_config_insecure_noverifytime (struct tls_config*) ; 
 struct tls_config* tls_config_new () ; 
 int tls_config_set_ca_file (struct tls_config*,scalar_t__) ; 
 int tls_config_set_cert_file (struct tls_config*,scalar_t__) ; 
 int tls_config_set_ciphers (struct tls_config*,char*) ; 
 int tls_config_set_key_file (struct tls_config*,scalar_t__) ; 
 int tls_config_set_protocols (struct tls_config*,int /*<<< orphan*/ ) ; 
 int tls_configure (struct tls*,struct tls_config*) ; 
 int tls_connect_cbs (struct tls*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tls_error (struct tls*) ; 
 int /*<<< orphan*/  tls_free (struct tls*) ; 
 int tls_init () ; 
 int /*<<< orphan*/  tls_read_callback ; 
 struct tls* tls_server () ; 
 int /*<<< orphan*/  tls_write_callback ; 

__attribute__((used)) static int ff_tls_open(URLContext *h, const char *uri, int flags, AVDictionary **options)
{
    TLSContext *p = h->priv_data;
    TLSShared *c = &p->tls_shared;
    struct tls_config *cfg = NULL;
    int ret;

    if (tls_init() == -1) {
        ret = AVERROR(EIO);
        goto fail;
    }

    if ((ret = ff_tls_open_underlying(c, h, uri, options)) < 0)
        goto fail;

    p->ctx = !c->listen ? tls_client() : tls_server();
    if (!p->ctx) {
        ret = AVERROR(EIO);
        goto fail;
    }

    cfg = tls_config_new();
    if (!p->ctx) {
        ret = AVERROR(EIO);
        goto fail;
    }
    if (tls_config_set_protocols(cfg, TLS_PROTOCOLS_ALL) == -1)
        goto err_config;
    // While TLSv1.0 and TLSv1.1 are already enabled by the above,
    // we need to be less strict with ciphers so it works in practice.
    if (tls_config_set_ciphers(cfg, "compat") == -1)
        goto err_config;
    if (c->ca_file && tls_config_set_ca_file(cfg, c->ca_file) == -1)
        goto err_config;
    if (c->cert_file && tls_config_set_cert_file(cfg, c->cert_file) == -1)
        goto err_config;
    if (c->key_file && tls_config_set_key_file(cfg, c->key_file) == -1)
        goto err_config;
    if (!c->verify) {
        tls_config_insecure_noverifycert(cfg);
        tls_config_insecure_noverifyname(cfg);
        tls_config_insecure_noverifytime(cfg);
    }
    if (tls_configure(p->ctx, cfg) == -1)
        goto err_ctx;

    if (!c->listen) {
        ret = tls_connect_cbs(p->ctx, tls_read_callback, tls_write_callback,
            c->tcp, c->host);
    } else {
        struct tls *ctx_new;
        ret = tls_accept_cbs(p->ctx, &ctx_new, tls_read_callback,
            tls_write_callback, c->tcp);
        if (ret == 0) {
            // free "server" context and replace by "connection" context
            tls_free(p->ctx);
            p->ctx = ctx_new;
        }
    }
    if (ret == -1)
        goto err_ctx;

    tls_config_free(cfg);
    return 0;
err_config:
    av_log(h, AV_LOG_ERROR, "%s\n", tls_config_error(cfg));
    ret = AVERROR(EIO);
    goto fail;
err_ctx:
    av_log(h, AV_LOG_ERROR, "%s\n", tls_error(p->ctx));
    ret = AVERROR(EIO);
    /* fallthrough */
fail:
    if (cfg)
        tls_config_free(cfg);
    ff_tls_close(h);
    return ret;
}