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
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_6__ {scalar_t__ pos; int /*<<< orphan*/  h; } ;
typedef  TYPE_2__ SubfileContext ;

/* Variables and functions */
 scalar_t__ AVERROR_BUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_err2str (scalar_t__) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ffurl_seek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int slave_seek(URLContext *h)
{
    SubfileContext *c = h->priv_data;
    int64_t ret;

    if ((ret = ffurl_seek(c->h, c->pos, SEEK_SET)) != c->pos) {
        if (ret >= 0)
            ret = AVERROR_BUG;
        av_log(h, AV_LOG_ERROR, "Impossible to seek in file: %s\n",
               av_err2str(ret));
        return ret;
    }
    return 0;
}