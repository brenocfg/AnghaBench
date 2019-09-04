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
struct TYPE_7__ {int (* url_move ) (TYPE_2__*,TYPE_2__*) ;} ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVIO_FLAG_READ_WRITE ; 
 int /*<<< orphan*/  AVIO_FLAG_WRITE ; 
 int /*<<< orphan*/  ENOSYS ; 
 int ffurl_alloc (TYPE_2__**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffurl_close (TYPE_2__*) ; 
 int stub1 (TYPE_2__*,TYPE_2__*) ; 

int avpriv_io_move(const char *url_src, const char *url_dst)
{
    URLContext *h_src, *h_dst;
    int ret = ffurl_alloc(&h_src, url_src, AVIO_FLAG_READ_WRITE, NULL);
    if (ret < 0)
        return ret;
    ret = ffurl_alloc(&h_dst, url_dst, AVIO_FLAG_WRITE, NULL);
    if (ret < 0) {
        ffurl_close(h_src);
        return ret;
    }

    if (h_src->prot == h_dst->prot && h_src->prot->url_move)
        ret = h_src->prot->url_move(h_src, h_dst);
    else
        ret = AVERROR(ENOSYS);

    ffurl_close(h_src);
    ffurl_close(h_dst);
    return ret;
}