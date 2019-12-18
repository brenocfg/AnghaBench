#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* priv_data; int /*<<< orphan*/  interrupt_callback; int /*<<< orphan*/  flags; int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_9__ {int fd; int /*<<< orphan*/  listen_timeout; int /*<<< orphan*/  listen; } ;
typedef  TYPE_2__ TCPContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 int ff_accept (int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int ffurl_alloc (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffurl_closep (TYPE_1__**) ; 

__attribute__((used)) static int tcp_accept(URLContext *s, URLContext **c)
{
    TCPContext *sc = s->priv_data;
    TCPContext *cc;
    int ret;
    av_assert0(sc->listen);
    if ((ret = ffurl_alloc(c, s->filename, s->flags, &s->interrupt_callback)) < 0)
        return ret;
    cc = (*c)->priv_data;
    ret = ff_accept(sc->fd, sc->listen_timeout, s);
    if (ret < 0) {
        ffurl_closep(c);
        return ret;
    }
    cc->fd = ret;
    return 0;
}