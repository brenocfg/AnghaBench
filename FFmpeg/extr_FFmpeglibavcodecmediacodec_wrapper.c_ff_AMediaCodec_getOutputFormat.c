#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * jobject ;
struct TYPE_11__ {int /*<<< orphan*/  get_output_format_id; } ;
struct TYPE_13__ {TYPE_1__ jfields; int /*<<< orphan*/  object; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* DeleteLocalRef ) (TYPE_2__**,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* CallObjectMethod ) (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__* JNIEnv ;
typedef  int /*<<< orphan*/  FFAMediaFormat ;
typedef  TYPE_3__ FFAMediaCodec ;

/* Variables and functions */
 int /*<<< orphan*/  JNI_GET_ENV_OR_RETURN (TYPE_2__**,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ff_AMediaFormat_newFromObject (int /*<<< orphan*/ *) ; 
 scalar_t__ ff_jni_exception_check (TYPE_2__**,int,TYPE_3__*) ; 
 int /*<<< orphan*/ * stub1 (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__**,int /*<<< orphan*/ *) ; 

FFAMediaFormat* ff_AMediaCodec_getOutputFormat(FFAMediaCodec* codec)
{
    FFAMediaFormat *ret = NULL;
    JNIEnv *env = NULL;

    jobject mediaformat = NULL;

    JNI_GET_ENV_OR_RETURN(env, codec, NULL);

    mediaformat = (*env)->CallObjectMethod(env, codec->object, codec->jfields.get_output_format_id);
    if (ff_jni_exception_check(env, 1, codec) < 0) {
        goto fail;
    }

    ret = ff_AMediaFormat_newFromObject(mediaformat);
fail:
    if (mediaformat) {
        (*env)->DeleteLocalRef(env, mediaformat);
    }

    return ret;
}