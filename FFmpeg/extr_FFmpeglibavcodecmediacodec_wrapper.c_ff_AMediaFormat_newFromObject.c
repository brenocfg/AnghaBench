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
struct TYPE_14__ {int /*<<< orphan*/  jfields; int /*<<< orphan*/  object; int /*<<< orphan*/ * class; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* NewGlobalRef ) (TYPE_1__**,void*) ;} ;
typedef  TYPE_1__* JNIEnv ;
typedef  TYPE_2__ FFAMediaFormat ;

/* Variables and functions */
 int /*<<< orphan*/  amediaformat_class ; 
 int /*<<< orphan*/  av_freep (TYPE_2__**) ; 
 TYPE_2__* av_mallocz (int) ; 
 TYPE_1__** ff_jni_get_env (TYPE_2__*) ; 
 scalar_t__ ff_jni_init_jfields (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int /*<<< orphan*/  ff_jni_reset_jfields (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int /*<<< orphan*/  jni_amediaformat_mapping ; 
 int /*<<< orphan*/  stub1 (TYPE_1__**,void*) ; 

__attribute__((used)) static FFAMediaFormat *ff_AMediaFormat_newFromObject(void *object)
{
    JNIEnv *env = NULL;
    FFAMediaFormat *format = NULL;

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

    format->object = (*env)->NewGlobalRef(env, object);
    if (!format->object) {
        goto fail;
    }

    return format;
fail:
    ff_jni_reset_jfields(env, &format->jfields, jni_amediaformat_mapping, 1, format);

    av_freep(&format);

    return NULL;
}