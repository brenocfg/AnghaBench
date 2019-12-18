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
struct TYPE_7__ {TYPE_1__ tls_shared; scalar_t__ ctx; } ;
typedef  TYPE_3__ TLSContext ;

/* Variables and functions */
 int /*<<< orphan*/  ffurl_close (scalar_t__) ; 
 int /*<<< orphan*/  tls_close (scalar_t__) ; 
 int /*<<< orphan*/  tls_free (scalar_t__) ; 

__attribute__((used)) static int ff_tls_close(URLContext *h)
{
    TLSContext *p = h->priv_data;
    if (p->ctx) {
        tls_close(p->ctx);
        tls_free(p->ctx);
    }
    if (p->tls_shared.tcp)
        ffurl_close(p->tls_shared.tcp);
    return 0;
}