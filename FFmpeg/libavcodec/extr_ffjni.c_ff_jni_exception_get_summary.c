#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * jthrowable ;
typedef  int /*<<< orphan*/ * jstring ;
typedef  int /*<<< orphan*/ * jmethodID ;
typedef  int /*<<< orphan*/ * jclass ;
struct TYPE_27__ {int /*<<< orphan*/  (* DeleteLocalRef ) (TYPE_1__**,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* ExceptionClear ) (TYPE_1__**) ;scalar_t__ (* ExceptionCheck ) (TYPE_1__**) ;int /*<<< orphan*/ * (* CallObjectMethod ) (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* GetMethodID ) (TYPE_1__**,int /*<<< orphan*/ *,char*,char*) ;int /*<<< orphan*/ * (* GetObjectClass ) (TYPE_1__**,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__* JNIEnv ;
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  AV_BPRINT_SIZE_AUTOMATIC ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int av_bprint_finalize (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  av_bprint_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_bprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*) ; 
 char* ff_jni_jstring_to_utf_chars (TYPE_1__**,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub10 (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub11 (TYPE_1__**) ; 
 int /*<<< orphan*/  stub12 (TYPE_1__**) ; 
 int /*<<< orphan*/  stub13 (TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub14 (TYPE_1__**,int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ stub15 (TYPE_1__**) ; 
 int /*<<< orphan*/  stub16 (TYPE_1__**) ; 
 int /*<<< orphan*/ * stub17 (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub18 (TYPE_1__**) ; 
 int /*<<< orphan*/  stub19 (TYPE_1__**) ; 
 scalar_t__ stub2 (TYPE_1__**) ; 
 int /*<<< orphan*/  stub20 (TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub21 (TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub22 (TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub23 (TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__**) ; 
 int /*<<< orphan*/ * stub4 (TYPE_1__**,int /*<<< orphan*/ *) ; 
 scalar_t__ stub5 (TYPE_1__**) ; 
 int /*<<< orphan*/  stub6 (TYPE_1__**) ; 
 int /*<<< orphan*/ * stub7 (TYPE_1__**,int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ stub8 (TYPE_1__**) ; 
 int /*<<< orphan*/  stub9 (TYPE_1__**) ; 

int ff_jni_exception_get_summary(JNIEnv *env, jthrowable exception, char **error, void *log_ctx)
{
    int ret = 0;

    AVBPrint bp;

    char *name = NULL;
    char *message = NULL;

    jclass class_class = NULL;
    jmethodID get_name_id = NULL;

    jclass exception_class = NULL;
    jmethodID get_message_id = NULL;

    jstring string = NULL;

    av_bprint_init(&bp, 0, AV_BPRINT_SIZE_AUTOMATIC);

    exception_class = (*env)->GetObjectClass(env, exception);
    if ((*env)->ExceptionCheck(env)) {
        (*env)->ExceptionClear(env);
        av_log(log_ctx, AV_LOG_ERROR, "Could not find Throwable class\n");
        ret = AVERROR_EXTERNAL;
        goto done;
    }

    class_class = (*env)->GetObjectClass(env, exception_class);
    if ((*env)->ExceptionCheck(env)) {
        (*env)->ExceptionClear(env);
        av_log(log_ctx, AV_LOG_ERROR, "Could not find Throwable class's class\n");
        ret = AVERROR_EXTERNAL;
        goto done;
    }

    get_name_id = (*env)->GetMethodID(env, class_class, "getName", "()Ljava/lang/String;");
    if ((*env)->ExceptionCheck(env)) {
        (*env)->ExceptionClear(env);
        av_log(log_ctx, AV_LOG_ERROR, "Could not find method Class.getName()\n");
        ret = AVERROR_EXTERNAL;
        goto done;
    }

    string = (*env)->CallObjectMethod(env, exception_class, get_name_id);
    if ((*env)->ExceptionCheck(env)) {
        (*env)->ExceptionClear(env);
        av_log(log_ctx, AV_LOG_ERROR, "Class.getName() threw an exception\n");
        ret = AVERROR_EXTERNAL;
        goto done;
    }

    if (string) {
        name = ff_jni_jstring_to_utf_chars(env, string, log_ctx);
        (*env)->DeleteLocalRef(env, string);
        string = NULL;
    }

    get_message_id = (*env)->GetMethodID(env, exception_class, "getMessage", "()Ljava/lang/String;");
    if ((*env)->ExceptionCheck(env)) {
        (*env)->ExceptionClear(env);
        av_log(log_ctx, AV_LOG_ERROR, "Could not find method java/lang/Throwable.getMessage()\n");
        ret = AVERROR_EXTERNAL;
        goto done;
    }

    string = (*env)->CallObjectMethod(env, exception, get_message_id);
    if ((*env)->ExceptionCheck(env)) {
        (*env)->ExceptionClear(env);
        av_log(log_ctx, AV_LOG_ERROR, "Throwable.getMessage() threw an exception\n");
        ret = AVERROR_EXTERNAL;
        goto done;
    }

    if (string) {
        message = ff_jni_jstring_to_utf_chars(env, string, log_ctx);
        (*env)->DeleteLocalRef(env, string);
        string = NULL;
    }

    if (name && message) {
        av_bprintf(&bp, "%s: %s", name, message);
    } else if (name && !message) {
        av_bprintf(&bp, "%s occurred", name);
    } else if (!name && message) {
        av_bprintf(&bp, "Exception: %s", message);
    } else {
        av_log(log_ctx, AV_LOG_WARNING, "Could not retrieve exception name and message\n");
        av_bprintf(&bp, "Exception occurred");
    }

    ret = av_bprint_finalize(&bp, error);
done:

    av_free(name);
    av_free(message);

    if (class_class) {
        (*env)->DeleteLocalRef(env, class_class);
    }

    if (exception_class) {
        (*env)->DeleteLocalRef(env, exception_class);
    }

    if (string) {
        (*env)->DeleteLocalRef(env, string);
    }

    return ret;
}