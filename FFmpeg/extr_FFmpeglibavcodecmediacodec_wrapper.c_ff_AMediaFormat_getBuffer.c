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
typedef  int /*<<< orphan*/ * jstring ;
typedef  int /*<<< orphan*/ * jobject ;
typedef  int /*<<< orphan*/  jboolean ;
struct TYPE_17__ {int /*<<< orphan*/  get_bytebuffer_id; int /*<<< orphan*/  contains_key_id; } ;
struct TYPE_19__ {TYPE_1__ jfields; int /*<<< orphan*/  object; } ;
struct TYPE_18__ {size_t (* GetDirectBufferCapacity ) (TYPE_2__**,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* DeleteLocalRef ) (TYPE_2__**,int /*<<< orphan*/ *) ;void* (* GetDirectBufferAddress ) (TYPE_2__**,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* CallObjectMethod ) (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* CallBooleanMethod ) (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__* JNIEnv ;
typedef  TYPE_3__ FFAMediaFormat ;

/* Variables and functions */
 int /*<<< orphan*/  JNI_GET_ENV_OR_RETURN (TYPE_2__**,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 void* av_malloc (size_t) ; 
 int ff_jni_exception_check (TYPE_2__**,int,TYPE_3__*) ; 
 int /*<<< orphan*/ * ff_jni_utf_chars_to_jstring (TYPE_2__**,char const*,TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub2 (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* stub3 (TYPE_2__**,int /*<<< orphan*/ *) ; 
 size_t stub4 (TYPE_2__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (TYPE_2__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (TYPE_2__**,int /*<<< orphan*/ *) ; 

int ff_AMediaFormat_getBuffer(FFAMediaFormat* format, const char *name, void** data, size_t *size)
{
    int ret = 1;

    JNIEnv *env = NULL;
    jstring key = NULL;
    jboolean contains_key;
    jobject result = NULL;

    av_assert0(format != NULL);

    JNI_GET_ENV_OR_RETURN(env, format, 0);

    key = ff_jni_utf_chars_to_jstring(env, name, format);
    if (!key) {
        ret = 0;
        goto fail;
    }

    contains_key = (*env)->CallBooleanMethod(env, format->object, format->jfields.contains_key_id, key);
    if (!contains_key || (ret = ff_jni_exception_check(env, 1, format)) < 0) {
        ret = 0;
        goto fail;
    }

    result = (*env)->CallObjectMethod(env, format->object, format->jfields.get_bytebuffer_id, key);
    if ((ret = ff_jni_exception_check(env, 1, format)) < 0) {
        ret = 0;
        goto fail;
    }

    *data = (*env)->GetDirectBufferAddress(env, result);
    *size = (*env)->GetDirectBufferCapacity(env, result);

    if (*data && *size) {
        void *src = *data;
        *data = av_malloc(*size);
        if (!*data) {
            ret = 0;
            goto fail;
        }

        memcpy(*data, src, *size);
    }

    ret = 1;
fail:
    if (key) {
        (*env)->DeleteLocalRef(env, key);
    }

    if (result) {
        (*env)->DeleteLocalRef(env, result);
    }

    return ret;
}