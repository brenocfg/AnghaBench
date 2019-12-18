#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_16__ {int /*<<< orphan*/  size_id; int /*<<< orphan*/  presentation_time_us_id; int /*<<< orphan*/  offset_id; int /*<<< orphan*/  flags_id; int /*<<< orphan*/  dequeue_output_buffer_id; } ;
struct TYPE_19__ {TYPE_1__ jfields; int /*<<< orphan*/  buffer_info; int /*<<< orphan*/  object; } ;
struct TYPE_18__ {int /*<<< orphan*/  size; int /*<<< orphan*/  presentationTimeUs; int /*<<< orphan*/  offset; int /*<<< orphan*/  flags; } ;
struct TYPE_17__ {int (* CallIntMethod ) (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* GetIntField ) (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* GetLongField ) (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__* JNIEnv ;
typedef  TYPE_3__ FFAMediaCodecBufferInfo ;
typedef  TYPE_4__ FFAMediaCodec ;

/* Variables and functions */
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  JNI_GET_ENV_OR_RETURN (TYPE_2__**,TYPE_4__*,int) ; 
 scalar_t__ ff_jni_exception_check (TYPE_2__**,int,TYPE_4__*) ; 
 int stub1 (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ssize_t ff_AMediaCodec_dequeueOutputBuffer(FFAMediaCodec* codec, FFAMediaCodecBufferInfo *info, int64_t timeoutUs)
{
    int ret = 0;
    JNIEnv *env = NULL;

    JNI_GET_ENV_OR_RETURN(env, codec, AVERROR_EXTERNAL);

    ret = (*env)->CallIntMethod(env, codec->object, codec->jfields.dequeue_output_buffer_id, codec->buffer_info, timeoutUs);
    if (ff_jni_exception_check(env, 1, codec) < 0) {
        return AVERROR_EXTERNAL;
    }

    info->flags = (*env)->GetIntField(env, codec->buffer_info, codec->jfields.flags_id);
    if (ff_jni_exception_check(env, 1, codec) < 0) {
        return AVERROR_EXTERNAL;
    }

    info->offset = (*env)->GetIntField(env, codec->buffer_info, codec->jfields.offset_id);
    if (ff_jni_exception_check(env, 1, codec) < 0) {
        return AVERROR_EXTERNAL;
    }

    info->presentationTimeUs = (*env)->GetLongField(env, codec->buffer_info, codec->jfields.presentation_time_us_id);
    if (ff_jni_exception_check(env, 1, codec) < 0) {
        return AVERROR_EXTERNAL;
    }

    info->size = (*env)->GetIntField(env, codec->buffer_info, codec->jfields.size_id);
    if (ff_jni_exception_check(env, 1, codec) < 0) {
        return AVERROR_EXTERNAL;
    }

    return ret;
}