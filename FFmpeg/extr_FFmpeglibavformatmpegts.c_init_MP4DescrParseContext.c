#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int max_descr_count; int /*<<< orphan*/ * active_descr; int /*<<< orphan*/ * descr; scalar_t__ descr_count; scalar_t__ level; int /*<<< orphan*/ * s; int /*<<< orphan*/  pb; } ;
typedef  int /*<<< orphan*/  Mp4Descr ;
typedef  TYPE_1__ MP4DescrParseContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int ffio_init_context (int /*<<< orphan*/ *,unsigned char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_MP4DescrParseContext(MP4DescrParseContext *d, AVFormatContext *s,
                                     const uint8_t *buf, unsigned size,
                                     Mp4Descr *descr, int max_descr_count)
{
    int ret;
    if (size > (1 << 30))
        return AVERROR_INVALIDDATA;

    if ((ret = ffio_init_context(&d->pb, (unsigned char *)buf, size, 0,
                                 NULL, NULL, NULL, NULL)) < 0)
        return ret;

    d->s               = s;
    d->level           = 0;
    d->descr_count     = 0;
    d->descr           = descr;
    d->active_descr    = NULL;
    d->max_descr_count = max_descr_count;

    return 0;
}