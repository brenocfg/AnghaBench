#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int (* GetEnv ) (TYPE_1__**,void**,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* AttachCurrentThread ) (TYPE_1__**,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  JNI_EDETACHED 130 
#define  JNI_EVERSION 129 
#define  JNI_OK 128 
 int /*<<< orphan*/  JNI_VERSION_1_6 ; 
 TYPE_1__** av_jni_get_java_vm (void*) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  current_env ; 
 TYPE_1__** java_vm ; 
 int /*<<< orphan*/  jni_create_pthread_key ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  once ; 
 int /*<<< orphan*/ * pthread_getspecific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_setspecific (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_1__**,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__**,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

JNIEnv *ff_jni_get_env(void *log_ctx)
{
    int ret = 0;
    JNIEnv *env = NULL;

    pthread_mutex_lock(&lock);
    if (java_vm == NULL) {
        java_vm = av_jni_get_java_vm(log_ctx);
    }

    if (!java_vm) {
        av_log(log_ctx, AV_LOG_ERROR, "No Java virtual machine has been registered\n");
        goto done;
    }

    pthread_once(&once, jni_create_pthread_key);

    if ((env = pthread_getspecific(current_env)) != NULL) {
        goto done;
    }

    ret = (*java_vm)->GetEnv(java_vm, (void **)&env, JNI_VERSION_1_6);
    switch(ret) {
    case JNI_EDETACHED:
        if ((*java_vm)->AttachCurrentThread(java_vm, &env, NULL) != 0) {
            av_log(log_ctx, AV_LOG_ERROR, "Failed to attach the JNI environment to the current thread\n");
            env = NULL;
        } else {
            pthread_setspecific(current_env, env);
        }
        break;
    case JNI_OK:
        break;
    case JNI_EVERSION:
        av_log(log_ctx, AV_LOG_ERROR, "The specified JNI version is not supported\n");
        break;
    default:
        av_log(log_ctx, AV_LOG_ERROR, "Failed to get the JNI environment attached to this thread\n");
        break;
    }

done:
    pthread_mutex_unlock(&lock);
    return env;
}