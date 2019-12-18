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
struct TYPE_6__ {scalar_t__ end; scalar_t__ start; scalar_t__ pos; int /*<<< orphan*/  h; } ;
typedef  TYPE_2__ SubfileContext ;

/* Variables and functions */
 scalar_t__ AVERROR (int /*<<< orphan*/ ) ; 
 int AVSEEK_SIZE ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ INT64_MAX ; 
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 scalar_t__ ffurl_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int slave_seek (TYPE_1__*) ; 

__attribute__((used)) static int64_t subfile_seek(URLContext *h, int64_t pos, int whence)
{
    SubfileContext *c = h->priv_data;
    int64_t new_pos, end;
    int ret;

    if (whence == AVSEEK_SIZE || whence == SEEK_END) {
        end = c->end;
        if (end == INT64_MAX && (end = ffurl_seek(c->h, 0, AVSEEK_SIZE)) < 0)
            return end;
    }

    if (whence == AVSEEK_SIZE)
        return end - c->start;
    switch (whence) {
    case SEEK_SET:
        new_pos = c->start + pos;
        break;
    case SEEK_CUR:
        new_pos = c->pos + pos;
        break;
    case SEEK_END:
        new_pos = end + pos;
        break;
    }
    if (new_pos < c->start)
        return AVERROR(EINVAL);
    c->pos = new_pos;
    if ((ret = slave_seek(h)) < 0)
        return ret;
    return c->pos - c->start;
}