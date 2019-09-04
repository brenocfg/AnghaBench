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
struct TYPE_10__ {TYPE_1__* prot; } ;
typedef  TYPE_2__ URLContext ;
struct TYPE_11__ {TYPE_2__* url_context; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* url_close_dir ) (TYPE_2__*) ;} ;
typedef  TYPE_3__ AVIODirContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_assert0 (TYPE_3__**) ; 
 int /*<<< orphan*/  av_freep (TYPE_3__**) ; 
 int /*<<< orphan*/  ffurl_close (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

int avio_close_dir(AVIODirContext **s)
{
    URLContext *h;

    av_assert0(s);
    if (!(*s) || !(*s)->url_context)
        return AVERROR(EINVAL);
    h = (*s)->url_context;
    h->prot->url_close_dir(h);
    ffurl_close(h);
    av_freep(s);
    *s = NULL;
    return 0;
}