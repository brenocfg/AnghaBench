#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* priv_data; int /*<<< orphan*/  interrupt_callback; int /*<<< orphan*/  flags; int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_10__ {int is_multi_client; TYPE_1__* hd; int /*<<< orphan*/  listen; } ;
typedef  TYPE_2__ HTTPContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 int ffurl_accept (TYPE_1__*,TYPE_1__**) ; 
 int ffurl_alloc (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffurl_closep (TYPE_1__**) ; 

__attribute__((used)) static int http_accept(URLContext *s, URLContext **c)
{
    int ret;
    HTTPContext *sc = s->priv_data;
    HTTPContext *cc;
    URLContext *sl = sc->hd;
    URLContext *cl = NULL;

    av_assert0(sc->listen);
    if ((ret = ffurl_alloc(c, s->filename, s->flags, &sl->interrupt_callback)) < 0)
        goto fail;
    cc = (*c)->priv_data;
    if ((ret = ffurl_accept(sl, &cl)) < 0)
        goto fail;
    cc->hd = cl;
    cc->is_multi_client = 1;
    return 0;
fail:
    if (c) {
        ffurl_closep(c);
    }
    return ret;
}