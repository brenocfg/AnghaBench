#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* prot; } ;
typedef  TYPE_2__ URLContext ;
struct TYPE_7__ {int (* url_accept ) (TYPE_2__*,TYPE_2__**) ;} ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int stub1 (TYPE_2__*,TYPE_2__**) ; 

int ffurl_accept(URLContext *s, URLContext **c)
{
    av_assert0(!*c);
    if (s->prot->url_accept)
        return s->prot->url_accept(s, c);
    return AVERROR(EBADF);
}