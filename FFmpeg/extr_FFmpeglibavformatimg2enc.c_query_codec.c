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
 int FF_COMPLIANCE_NORMAL ; 
 TYPE_1__* ff_img_tags ; 

__attribute__((used)) static int query_codec(enum AVCodecID id, int std_compliance)
{
    int i;
    for (i = 0; ff_img_tags[i].id != AV_CODEC_ID_NONE; i++)
        if (ff_img_tags[i].id == id)
            return 1;

    // Anything really can be stored in img2
    return std_compliance < FF_COMPLIANCE_NORMAL;
}