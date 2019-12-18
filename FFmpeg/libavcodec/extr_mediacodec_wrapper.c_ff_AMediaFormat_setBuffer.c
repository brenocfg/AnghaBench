#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * jstring ;
typedef  int /*<<< orphan*/ * jobject ;
struct TYPE_15__ {int /*<<< orphan*/  set_bytebuffer_id; } ;
struct TYPE_17__ {TYPE_1__ jfields; int /*<<< orphan*/  object; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* DeleteLocalRef ) (TYPE_2__**,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* CallVoidMethod ) (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* NewDirectByteBuffer ) (TYPE_2__**,void*,size_t) ;} ;
typedef  TYPE_2__* JNIEnv ;
typedef  TYPE_3__ FFAMediaFormat ;

/* Variables and functions */
 int /*<<< orphan*/  JNI_GET_ENV_OR_RETURN_VOID (TYPE_2__**,TYPE_3__*) ; 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 void* av_malloc (size_t) ; 
 scalar_t__ ff_jni_exception_check (TYPE_2__**,int,TYPE_3__*) ; 
 int /*<<< orphan*/ * ff_jni_utf_chars_to_jstring (TYPE_2__**,char const*,TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 int /*<<< orphan*/ * stub1 (TYPE_2__**,void*,size_t) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__**,int /*<<< orphan*/ *) ; 

void ff_AMediaFormat_setBuffer(FFAMediaFormat* format, const char* name, void* data, size_t size)
{
    JNIEnv *env = NULL;
    jstring key = NULL;
    jobject buffer = NULL;
    void *buffer_data = NULL;

    av_assert0(format != NULL);

    JNI_GET_ENV_OR_RETURN_VOID(env, format);

    key = ff_jni_utf_chars_to_jstring(env, name, format);
    if (!key) {
        goto fail;
    }

    if (!data || !size) {
        goto fail;
    }

    buffer_data = av_malloc(size);
    if (!buffer_data) {
        goto fail;
    }

    memcpy(buffer_data, data, size);

    buffer = (*env)->NewDirectByteBuffer(env, buffer_data, size);
    if (!buffer) {
        goto fail;
    }

    (*env)->CallVoidMethod(env, format->object, format->jfields.set_bytebuffer_id, key, buffer);
    if (ff_jni_exception_check(env, 1, format) < 0) {
        goto fail;
    }

fail:
    if (key) {
        (*env)->DeleteLocalRef(env, key);
    }

    if (buffer) {
        (*env)->DeleteLocalRef(env, buffer);
    }
}