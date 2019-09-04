#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_6__ {TYPE_1__* prot; } ;
typedef  TYPE_2__ URLContext ;
struct TYPE_5__ {int /*<<< orphan*/  (* url_seek ) (TYPE_2__*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AVERROR (int /*<<< orphan*/ ) ; 
 int AVSEEK_FORCE ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

int64_t ffurl_seek(URLContext *h, int64_t pos, int whence)
{
    int64_t ret;

    if (!h->prot->url_seek)
        return AVERROR(ENOSYS);
    ret = h->prot->url_seek(h, pos, whence & ~AVSEEK_FORCE);
    return ret;
}