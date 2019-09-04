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
struct TYPE_3__ {scalar_t__ pict_type; } ;
typedef  int /*<<< orphan*/ * CFDictionaryRef ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_PICTURE_TYPE_I ; 
 int /*<<< orphan*/ * CFDictionaryCreate (int /*<<< orphan*/ *,void const**,void const**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENOMEM ; 
 void const* kCFBooleanTrue ; 
 void const* kVTEncodeFrameOptionKey_ForceKeyFrame ; 

__attribute__((used)) static int create_encoder_dict_h264(const AVFrame *frame,
                                    CFDictionaryRef* dict_out)
{
    CFDictionaryRef dict = NULL;
    if (frame->pict_type == AV_PICTURE_TYPE_I) {
        const void *keys[] = { kVTEncodeFrameOptionKey_ForceKeyFrame };
        const void *vals[] = { kCFBooleanTrue };

        dict = CFDictionaryCreate(NULL, keys, vals, 1, NULL, NULL);
        if(!dict) return AVERROR(ENOMEM);
    }

    *dict_out = dict;
    return 0;
}