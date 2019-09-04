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
typedef  int /*<<< orphan*/  UID ;
struct TYPE_3__ {int profile; int level; } ;
typedef  TYPE_1__ AVCodecParameters ;

/* Variables and functions */
 int /*<<< orphan*/  const* mxf_mpeg2_codec_uls ; 

__attribute__((used)) static const UID *mxf_get_mpeg2_codec_ul(AVCodecParameters *par)
{
    int long_gop = 1;

    if (par->profile == 4) { // Main
        if (par->level == 8) // Main
            return &mxf_mpeg2_codec_uls[0+long_gop];
        else if (par->level == 4) // High
            return &mxf_mpeg2_codec_uls[4+long_gop];
        else if (par->level == 6) // High 14
            return &mxf_mpeg2_codec_uls[8+long_gop];
    } else if (par->profile == 0) { // 422
        if (par->level == 5) // Main
            return &mxf_mpeg2_codec_uls[2+long_gop];
        else if (par->level == 2) // High
            return &mxf_mpeg2_codec_uls[6+long_gop];
    }
    return NULL;
}