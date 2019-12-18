#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jthrowable ;
struct TYPE_10__ {int /*<<< orphan*/  (* DeleteLocalRef ) (TYPE_1__**,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ExceptionClear ) (TYPE_1__**) ;int /*<<< orphan*/  (* ExceptionOccurred ) (TYPE_1__**) ;int /*<<< orphan*/  (* ExceptionCheck ) (TYPE_1__**) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,char*) ; 
 int ff_jni_exception_get_summary (TYPE_1__**,int /*<<< orphan*/ ,char**,void*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__**) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__**) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__**) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__**) ; 
 int /*<<< orphan*/  stub5 (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (TYPE_1__**,int /*<<< orphan*/ ) ; 

int ff_jni_exception_check(JNIEnv *env, int log, void *log_ctx)
{
    int ret;

    jthrowable exception;

    char *message = NULL;

    if (!(*(env))->ExceptionCheck((env))) {
        return 0;
    }

    if (!log) {
        (*(env))->ExceptionClear((env));
        return -1;
    }

    exception = (*env)->ExceptionOccurred(env);
    (*(env))->ExceptionClear((env));

    if ((ret = ff_jni_exception_get_summary(env, exception, &message, log_ctx)) < 0) {
        (*env)->DeleteLocalRef(env, exception);
        return ret;
    }

    (*env)->DeleteLocalRef(env, exception);

    av_log(log_ctx, AV_LOG_ERROR, "%s\n", message);
    av_free(message);

    return -1;
}