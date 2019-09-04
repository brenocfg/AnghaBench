#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * jobject ;
struct TYPE_19__ {int /*<<< orphan*/  init_id; int /*<<< orphan*/  mediaformat_class; } ;
struct TYPE_18__ {TYPE_7__ jfields; int /*<<< orphan*/  object; int /*<<< orphan*/ * class; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* DeleteLocalRef ) (TYPE_1__**,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* NewGlobalRef ) (TYPE_1__**,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* NewObject ) (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__* JNIEnv ;
typedef  TYPE_2__ FFAMediaFormat ;

/* Variables and functions */
 int /*<<< orphan*/  amediaformat_class ; 
 int /*<<< orphan*/  av_freep (TYPE_2__**) ; 
 TYPE_2__* av_mallocz (int) ; 
 TYPE_1__** ff_jni_get_env (TYPE_2__*) ; 
 scalar_t__ ff_jni_init_jfields (TYPE_1__**,TYPE_7__*,int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int /*<<< orphan*/  ff_jni_reset_jfields (TYPE_1__**,TYPE_7__*,int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int /*<<< orphan*/  jni_amediaformat_mapping ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__**,int /*<<< orphan*/ *) ; 

FFAMediaFormat *ff_AMediaFormat_new(void)
{
    JNIEnv *env = NULL;
    FFAMediaFormat *format = NULL;
    jobject object = NULL;

    format = av_mallocz(sizeof(FFAMediaFormat));
    if (!format) {
        return NULL;
    }
    format->class = &amediaformat_class;

    env = ff_jni_get_env(format);
    if (!env) {
        av_freep(&format);
        return NULL;
    }

    if (ff_jni_init_jfields(env, &format->jfields, jni_amediaformat_mapping, 1, format) < 0) {
        goto fail;
    }

    object = (*env)->NewObject(env, format->jfields.mediaformat_class, format->jfields.init_id);
    if (!object) {
        goto fail;
    }

    format->object = (*env)->NewGlobalRef(env, object);
    if (!format->object) {
        goto fail;
    }

fail:
    if (object) {
        (*env)->DeleteLocalRef(env, object);
    }

    if (!format->object) {
        ff_jni_reset_jfields(env, &format->jfields, jni_amediaformat_mapping, 1, format);
        av_freep(&format);
    }

    return format;
}