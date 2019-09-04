#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * jstring ;
struct TYPE_6__ {int /*<<< orphan*/  (* ExceptionClear ) (TYPE_1__**) ;scalar_t__ (* ExceptionCheck ) (TYPE_1__**) ;int /*<<< orphan*/ * (* NewStringUTF ) (TYPE_1__**,char const*) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__**,char const*) ; 
 scalar_t__ stub2 (TYPE_1__**) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__**) ; 

jstring ff_jni_utf_chars_to_jstring(JNIEnv *env, const char *utf_chars, void *log_ctx)
{
    jstring ret;

    ret = (*env)->NewStringUTF(env, utf_chars);
    if ((*env)->ExceptionCheck(env)) {
        (*env)->ExceptionClear(env);
        av_log(log_ctx, AV_LOG_ERROR, "NewStringUTF() threw an exception\n");
        return NULL;
    }

    return ret;
}