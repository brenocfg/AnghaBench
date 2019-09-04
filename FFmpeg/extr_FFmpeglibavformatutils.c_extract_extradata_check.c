#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_8__ {int* codec_ids; } ;
struct TYPE_7__ {TYPE_1__* codecpar; } ;
struct TYPE_6__ {int const codec_id; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVBitStreamFilter ;

/* Variables and functions */
 int const AV_CODEC_ID_NONE ; 
 TYPE_3__* av_bsf_get_by_name (char*) ; 

__attribute__((used)) static int extract_extradata_check(AVStream *st)
{
    const AVBitStreamFilter *f;

    f = av_bsf_get_by_name("extract_extradata");
    if (!f)
        return 0;

    if (f->codec_ids) {
        const enum AVCodecID *ids;
        for (ids = f->codec_ids; *ids != AV_CODEC_ID_NONE; ids++)
            if (*ids == st->codecpar->codec_id)
                return 1;
    }

    return 0;
}