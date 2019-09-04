#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  URLContext ;
struct TYPE_7__ {TYPE_1__* opaque; } ;
struct TYPE_6__ {int /*<<< orphan*/ * h; } ;
typedef  TYPE_1__ AVIOInternal ;
typedef  TYPE_2__ AVIOContext ;

/* Variables and functions */
 int ffio_fdopen (TYPE_2__**,int /*<<< orphan*/ *) ; 
 int ffurl_accept (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

int avio_accept(AVIOContext *s, AVIOContext **c)
{
    int ret;
    AVIOInternal *internal = s->opaque;
    URLContext *sc = internal->h;
    URLContext *cc = NULL;
    ret = ffurl_accept(sc, &cc);
    if (ret < 0)
        return ret;
    return ffio_fdopen(c, cc);
}