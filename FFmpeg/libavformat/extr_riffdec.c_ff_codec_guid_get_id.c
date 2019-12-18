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
struct TYPE_3__ {scalar_t__ id; int /*<<< orphan*/  guid; } ;
typedef  TYPE_1__ AVCodecGuid ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_NONE ; 
 int /*<<< orphan*/  ff_guidcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

enum AVCodecID ff_codec_guid_get_id(const AVCodecGuid *guids, ff_asf_guid guid)
{
    int i;
    for (i = 0; guids[i].id != AV_CODEC_ID_NONE; i++)
        if (!ff_guidcmp(guids[i].guid, guid))
            return guids[i].id;
    return AV_CODEC_ID_NONE;
}