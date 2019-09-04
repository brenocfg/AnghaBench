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
typedef  int /*<<< orphan*/  ff_asf_guid ;
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_3__ {scalar_t__ id; int /*<<< orphan*/  const guid; } ;
typedef  TYPE_1__ AVCodecGuid ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_NONE ; 

const ff_asf_guid *ff_get_codec_guid(enum AVCodecID id, const AVCodecGuid *av_guid)
{
    int i;
    for (i = 0; av_guid[i].id != AV_CODEC_ID_NONE; i++) {
        if (id == av_guid[i].id)
            return &(av_guid[i].guid);
    }
    return NULL;
}