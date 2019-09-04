#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  info_output_format_changed_id; int /*<<< orphan*/  mediacodec_class; int /*<<< orphan*/  info_output_buffers_changed_id; int /*<<< orphan*/  info_try_again_later_id; int /*<<< orphan*/  configure_flag_encode_id; int /*<<< orphan*/  buffer_flag_key_frame_id; int /*<<< orphan*/  buffer_flag_end_of_stream_id; int /*<<< orphan*/  buffer_flag_codec_config_id; } ;
struct TYPE_19__ {TYPE_1__ jfields; int /*<<< orphan*/  INFO_OUTPUT_FORMAT_CHANGED; int /*<<< orphan*/  INFO_OUTPUT_BUFFERS_CHANGED; int /*<<< orphan*/  INFO_TRY_AGAIN_LATER; int /*<<< orphan*/  CONFIGURE_FLAG_ENCODE; int /*<<< orphan*/  BUFFER_FLAG_KEY_FRAME; int /*<<< orphan*/  BUFFER_FLAG_END_OF_STREAM; int /*<<< orphan*/  BUFFER_FLAG_CODEC_CONFIG; } ;
struct TYPE_18__ {int /*<<< orphan*/  (* GetStaticIntField ) (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__* JNIEnv ;
typedef  TYPE_3__ FFAMediaCodec ;

/* Variables and functions */
 int /*<<< orphan*/  AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  JNI_GET_ENV_OR_RETURN (TYPE_2__**,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int ff_jni_exception_check (TYPE_2__**,int,TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int codec_init_static_fields(FFAMediaCodec *codec)
{
    int ret = 0;
    JNIEnv *env = NULL;

    JNI_GET_ENV_OR_RETURN(env, codec, AVERROR_EXTERNAL);

    codec->INFO_TRY_AGAIN_LATER = (*env)->GetStaticIntField(env, codec->jfields.mediacodec_class, codec->jfields.info_try_again_later_id);
    if ((ret = ff_jni_exception_check(env, 1, codec)) < 0) {
        goto fail;
    }

    codec->BUFFER_FLAG_CODEC_CONFIG = (*env)->GetStaticIntField(env, codec->jfields.mediacodec_class, codec->jfields.buffer_flag_codec_config_id);
    if ((ret = ff_jni_exception_check(env, 1, codec)) < 0) {
        goto fail;
    }

    codec->BUFFER_FLAG_END_OF_STREAM = (*env)->GetStaticIntField(env, codec->jfields.mediacodec_class, codec->jfields.buffer_flag_end_of_stream_id);
    if ((ret = ff_jni_exception_check(env, 1, codec)) < 0) {
        goto fail;
    }

    if (codec->jfields.buffer_flag_key_frame_id) {
        codec->BUFFER_FLAG_KEY_FRAME = (*env)->GetStaticIntField(env, codec->jfields.mediacodec_class, codec->jfields.buffer_flag_key_frame_id);
        if ((ret = ff_jni_exception_check(env, 1, codec)) < 0) {
            goto fail;
        }
    }

    codec->CONFIGURE_FLAG_ENCODE = (*env)->GetStaticIntField(env, codec->jfields.mediacodec_class, codec->jfields.configure_flag_encode_id);
    if ((ret = ff_jni_exception_check(env, 1, codec)) < 0) {
        goto fail;
    }

    codec->INFO_TRY_AGAIN_LATER = (*env)->GetStaticIntField(env, codec->jfields.mediacodec_class, codec->jfields.info_try_again_later_id);
    if ((ret = ff_jni_exception_check(env, 1, codec)) < 0) {
        goto fail;
    }

    codec->INFO_OUTPUT_BUFFERS_CHANGED = (*env)->GetStaticIntField(env, codec->jfields.mediacodec_class, codec->jfields.info_output_buffers_changed_id);
    if ((ret = ff_jni_exception_check(env, 1, codec)) < 0) {
        goto fail;
    }

    codec->INFO_OUTPUT_FORMAT_CHANGED = (*env)->GetStaticIntField(env, codec->jfields.mediacodec_class, codec->jfields.info_output_format_changed_id);
    if ((ret = ff_jni_exception_check(env, 1, codec)) < 0) {
        goto fail;
    }

fail:

    return ret;
}