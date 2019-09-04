#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct JNIAMediaCodecListFields {int /*<<< orphan*/  codec_profile_level_class; scalar_t__ hevc_profile_main10_id; scalar_t__ hevc_profile_main_id; scalar_t__ avc_profile_high444_id; scalar_t__ avc_profile_high422_id; scalar_t__ avc_profile_high10_id; scalar_t__ avc_profile_high_id; scalar_t__ avc_profile_extended_id; scalar_t__ avc_profile_main_id; scalar_t__ avc_profile_baseline_id; int /*<<< orphan*/  member_0; } ;
typedef  scalar_t__ jfieldID ;
struct TYPE_14__ {scalar_t__ codec_id; int profile; } ;
struct TYPE_13__ {int (* GetStaticIntField ) (TYPE_1__**,int /*<<< orphan*/ ,scalar_t__) ;} ;
typedef  TYPE_1__* JNIEnv ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_H264 ; 
 scalar_t__ AV_CODEC_ID_HEVC ; 
#define  FF_PROFILE_H264_BASELINE 142 
#define  FF_PROFILE_H264_CONSTRAINED_BASELINE 141 
#define  FF_PROFILE_H264_EXTENDED 140 
#define  FF_PROFILE_H264_HIGH 139 
#define  FF_PROFILE_H264_HIGH_10 138 
#define  FF_PROFILE_H264_HIGH_10_INTRA 137 
#define  FF_PROFILE_H264_HIGH_422 136 
#define  FF_PROFILE_H264_HIGH_422_INTRA 135 
#define  FF_PROFILE_H264_HIGH_444 134 
#define  FF_PROFILE_H264_HIGH_444_INTRA 133 
#define  FF_PROFILE_H264_HIGH_444_PREDICTIVE 132 
#define  FF_PROFILE_H264_MAIN 131 
#define  FF_PROFILE_HEVC_MAIN 130 
#define  FF_PROFILE_HEVC_MAIN_10 129 
#define  FF_PROFILE_HEVC_MAIN_STILL_PICTURE 128 
 int /*<<< orphan*/  JNI_GET_ENV_OR_RETURN (TYPE_1__**,TYPE_2__*,int) ; 
 scalar_t__ ff_jni_exception_check (TYPE_1__**,int,TYPE_2__*) ; 
 scalar_t__ ff_jni_init_jfields (TYPE_1__**,struct JNIAMediaCodecListFields*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ff_jni_reset_jfields (TYPE_1__**,struct JNIAMediaCodecListFields*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  jni_amediacodeclist_mapping ; 
 int stub1 (TYPE_1__**,int /*<<< orphan*/ ,scalar_t__) ; 

int ff_AMediaCodecProfile_getProfileFromAVCodecContext(AVCodecContext *avctx)
{
    int ret = -1;

    JNIEnv *env = NULL;
    struct JNIAMediaCodecListFields jfields = { 0 };
    jfieldID field_id = 0;

    JNI_GET_ENV_OR_RETURN(env, avctx, -1);

    if (ff_jni_init_jfields(env, &jfields, jni_amediacodeclist_mapping, 0, avctx) < 0) {
        goto done;
    }

    if (avctx->codec_id == AV_CODEC_ID_H264) {
        switch(avctx->profile) {
        case FF_PROFILE_H264_BASELINE:
        case FF_PROFILE_H264_CONSTRAINED_BASELINE:
            field_id = jfields.avc_profile_baseline_id;
            break;
        case FF_PROFILE_H264_MAIN:
            field_id = jfields.avc_profile_main_id;
            break;
        case FF_PROFILE_H264_EXTENDED:
            field_id = jfields.avc_profile_extended_id;
            break;
        case FF_PROFILE_H264_HIGH:
            field_id = jfields.avc_profile_high_id;
            break;
        case FF_PROFILE_H264_HIGH_10:
        case FF_PROFILE_H264_HIGH_10_INTRA:
            field_id = jfields.avc_profile_high10_id;
            break;
        case FF_PROFILE_H264_HIGH_422:
        case FF_PROFILE_H264_HIGH_422_INTRA:
            field_id = jfields.avc_profile_high422_id;
            break;
        case FF_PROFILE_H264_HIGH_444:
        case FF_PROFILE_H264_HIGH_444_INTRA:
        case FF_PROFILE_H264_HIGH_444_PREDICTIVE:
            field_id = jfields.avc_profile_high444_id;
            break;
        }
    } else if (avctx->codec_id == AV_CODEC_ID_HEVC) {
        switch (avctx->profile) {
        case FF_PROFILE_HEVC_MAIN:
        case FF_PROFILE_HEVC_MAIN_STILL_PICTURE:
            field_id = jfields.hevc_profile_main_id;
            break;
        case FF_PROFILE_HEVC_MAIN_10:
            field_id = jfields.hevc_profile_main10_id;
            break;
        }
    }

        if (field_id) {
            ret = (*env)->GetStaticIntField(env, jfields.codec_profile_level_class, field_id);
            if (ff_jni_exception_check(env, 1, avctx) < 0) {
                ret = -1;
                goto done;
            }
        }

done:
    ff_jni_reset_jfields(env, &jfields, jni_amediacodeclist_mapping, 0, avctx);

    return ret;
}