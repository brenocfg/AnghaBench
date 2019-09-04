#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  release_id; } ;
struct TYPE_16__ {TYPE_7__ jfields; int /*<<< orphan*/ * buffer_info; int /*<<< orphan*/ * object; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* DeleteGlobalRef ) (TYPE_1__**,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* CallVoidMethod ) (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__* JNIEnv ;
typedef  TYPE_2__ FFAMediaCodec ;

/* Variables and functions */
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  JNI_GET_ENV_OR_RETURN (TYPE_1__**,TYPE_2__*,int) ; 
 int /*<<< orphan*/  av_freep (TYPE_2__**) ; 
 scalar_t__ ff_jni_exception_check (TYPE_1__**,int,TYPE_2__*) ; 
 int /*<<< orphan*/  ff_jni_reset_jfields (TYPE_1__**,TYPE_7__*,int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int /*<<< orphan*/  jni_amediacodec_mapping ; 
 int /*<<< orphan*/  stub1 (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__**,int /*<<< orphan*/ *) ; 

int ff_AMediaCodec_delete(FFAMediaCodec* codec)
{
    int ret = 0;

    JNIEnv *env = NULL;

    if (!codec) {
        return 0;
    }

    JNI_GET_ENV_OR_RETURN(env, codec, AVERROR_EXTERNAL);

    (*env)->CallVoidMethod(env, codec->object, codec->jfields.release_id);
    if (ff_jni_exception_check(env, 1, codec) < 0) {
        ret = AVERROR_EXTERNAL;
    }

    (*env)->DeleteGlobalRef(env, codec->object);
    codec->object = NULL;

    (*env)->DeleteGlobalRef(env, codec->buffer_info);
    codec->buffer_info = NULL;

    ff_jni_reset_jfields(env, &codec->jfields, jni_amediacodec_mapping, 1, codec);

    av_freep(&codec);

    return ret;
}