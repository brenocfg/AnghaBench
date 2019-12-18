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
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_3__ {int tag; int format; } ;
typedef  TYPE_1__ XVTagFormatMap ;

/* Variables and functions */
 TYPE_1__* tag_codec_map ; 

__attribute__((used)) static int xv_get_tag_from_format(enum AVPixelFormat format)
{
    const XVTagFormatMap *m = tag_codec_map;
    int i;
    for (i = 0; m->tag; m = &tag_codec_map[++i]) {
        if (m->format == format)
            return m->tag;
    }
    return 0;
}