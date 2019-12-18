#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_2__ {scalar_t__ id; } ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_NONE ; 
 TYPE_1__* ff_webm_codec_tags ; 

__attribute__((used)) static int webm_query_codec(enum AVCodecID codec_id, int std_compliance)
{
    int i;
    for (i = 0; ff_webm_codec_tags[i].id != AV_CODEC_ID_NONE; i++)
        if (ff_webm_codec_tags[i].id == codec_id)
            return 1;

    return 0;
}