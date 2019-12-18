#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * jstring ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_13__ {int /*<<< orphan*/  set_long_id; } ;
struct TYPE_15__ {TYPE_1__ jfields; int /*<<< orphan*/  object; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* DeleteLocalRef ) (TYPE_2__**,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* CallVoidMethod ) (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__* JNIEnv ;
typedef  TYPE_3__ FFAMediaFormat ;

/* Variables and functions */
 int /*<<< orphan*/  JNI_GET_ENV_OR_RETURN_VOID (TYPE_2__**,TYPE_3__*) ; 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 scalar_t__ ff_jni_exception_check (TYPE_2__**,int,TYPE_3__*) ; 
 int /*<<< orphan*/ * ff_jni_utf_chars_to_jstring (TYPE_2__**,char const*,TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__**,int /*<<< orphan*/ *) ; 

void ff_AMediaFormat_setInt64(FFAMediaFormat* format, const char* name, int64_t value)
{
    JNIEnv *env = NULL;
    jstring key = NULL;

    av_assert0(format != NULL);

    JNI_GET_ENV_OR_RETURN_VOID(env, format);

    key = ff_jni_utf_chars_to_jstring(env, name, format);
    if (!key) {
        goto fail;
    }

    (*env)->CallVoidMethod(env, format->object, format->jfields.set_long_id, key, value);
    if (ff_jni_exception_check(env, 1, format) < 0) {
        goto fail;
    }

fail:
    if (key) {
        (*env)->DeleteLocalRef(env, key);
    }
}