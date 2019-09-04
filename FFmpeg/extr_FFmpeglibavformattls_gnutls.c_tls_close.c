#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* priv_data; } ;
typedef  TYPE_2__ URLContext ;
struct TYPE_5__ {scalar_t__ tcp; } ;
struct TYPE_7__ {TYPE_1__ tls_shared; scalar_t__ cred; scalar_t__ session; scalar_t__ need_shutdown; } ;
typedef  TYPE_3__ TLSContext ;

/* Variables and functions */
 int /*<<< orphan*/  GNUTLS_SHUT_WR ; 
 int /*<<< orphan*/  ff_gnutls_deinit () ; 
 int /*<<< orphan*/  ffurl_close (scalar_t__) ; 
 int /*<<< orphan*/  gnutls_bye (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnutls_certificate_free_credentials (scalar_t__) ; 
 int /*<<< orphan*/  gnutls_deinit (scalar_t__) ; 

__attribute__((used)) static int tls_close(URLContext *h)
{
    TLSContext *c = h->priv_data;
    if (c->need_shutdown)
        gnutls_bye(c->session, GNUTLS_SHUT_WR);
    if (c->session)
        gnutls_deinit(c->session);
    if (c->cred)
        gnutls_certificate_free_credentials(c->cred);
    if (c->tls_shared.tcp)
        ffurl_close(c->tls_shared.tcp);
    ff_gnutls_deinit();
    return 0;
}