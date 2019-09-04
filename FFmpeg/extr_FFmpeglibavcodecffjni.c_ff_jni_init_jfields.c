#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct FFJniField {int mandatory; int type; int offset; int /*<<< orphan*/  signature; int /*<<< orphan*/  method; scalar_t__ name; } ;
typedef  int /*<<< orphan*/  jmethodID ;
typedef  int /*<<< orphan*/  jfieldID ;
typedef  int /*<<< orphan*/ * jclass ;
typedef  enum FFJniFieldType { ____Placeholder_FFJniFieldType } FFJniFieldType ;
struct TYPE_12__ {int /*<<< orphan*/  (* GetStaticMethodID ) (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* GetMethodID ) (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* GetStaticFieldID ) (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* GetFieldID ) (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* DeleteLocalRef ) (TYPE_1__**,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* NewGlobalRef ) (TYPE_1__**,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* FindClass ) (TYPE_1__**,scalar_t__) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int FF_JNI_CLASS ; 
#define  FF_JNI_FIELD 131 
#define  FF_JNI_METHOD 130 
#define  FF_JNI_STATIC_FIELD 129 
#define  FF_JNI_STATIC_METHOD 128 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*) ; 
 int ff_jni_exception_check (TYPE_1__**,int,void*) ; 
 int /*<<< orphan*/  ff_jni_reset_jfields (TYPE_1__**,void*,struct FFJniField const*,int,void*) ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__**,scalar_t__) ; 
 int /*<<< orphan*/ * stub2 (TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ff_jni_init_jfields(JNIEnv *env, void *jfields, const struct FFJniField *jfields_mapping, int global, void *log_ctx)
{
    int i, ret = 0;
    jclass last_clazz = NULL;

    for (i = 0; jfields_mapping[i].name; i++) {
        int mandatory = jfields_mapping[i].mandatory;
        enum FFJniFieldType type = jfields_mapping[i].type;

        if (type == FF_JNI_CLASS) {
            jclass clazz;

            last_clazz = NULL;

            clazz = (*env)->FindClass(env, jfields_mapping[i].name);
            if ((ret = ff_jni_exception_check(env, mandatory, log_ctx)) < 0 && mandatory) {
                goto done;
            }

            last_clazz = *(jclass*)((uint8_t*)jfields + jfields_mapping[i].offset) =
                    global ? (*env)->NewGlobalRef(env, clazz) : clazz;

            if (global) {
                (*env)->DeleteLocalRef(env, clazz);
            }

        } else {

            if (!last_clazz) {
                ret = AVERROR_EXTERNAL;
                break;
            }

            switch(type) {
            case FF_JNI_FIELD: {
                jfieldID field_id = (*env)->GetFieldID(env, last_clazz, jfields_mapping[i].method, jfields_mapping[i].signature);
                if ((ret = ff_jni_exception_check(env, mandatory, log_ctx)) < 0 && mandatory) {
                    goto done;
                }

                *(jfieldID*)((uint8_t*)jfields + jfields_mapping[i].offset) = field_id;
                break;
            }
            case FF_JNI_STATIC_FIELD: {
                jfieldID field_id = (*env)->GetStaticFieldID(env, last_clazz, jfields_mapping[i].method, jfields_mapping[i].signature);
                if ((ret = ff_jni_exception_check(env, mandatory, log_ctx)) < 0 && mandatory) {
                    goto done;
                }

                *(jfieldID*)((uint8_t*)jfields + jfields_mapping[i].offset) = field_id;
                break;
            }
            case FF_JNI_METHOD: {
                jmethodID method_id = (*env)->GetMethodID(env, last_clazz, jfields_mapping[i].method, jfields_mapping[i].signature);
                if ((ret = ff_jni_exception_check(env, mandatory, log_ctx)) < 0 && mandatory) {
                    goto done;
                }

                *(jmethodID*)((uint8_t*)jfields + jfields_mapping[i].offset) = method_id;
                break;
            }
            case FF_JNI_STATIC_METHOD: {
                jmethodID method_id = (*env)->GetStaticMethodID(env, last_clazz, jfields_mapping[i].method, jfields_mapping[i].signature);
                if ((ret = ff_jni_exception_check(env, mandatory, log_ctx)) < 0 && mandatory) {
                    goto done;
                }

                *(jmethodID*)((uint8_t*)jfields + jfields_mapping[i].offset) = method_id;
                break;
            }
            default:
                av_log(log_ctx, AV_LOG_ERROR, "Unknown JNI field type\n");
                ret = AVERROR(EINVAL);
                goto done;
            }

            ret = 0;
        }
    }

done:
    if (ret < 0) {
        /* reset jfields in case of failure so it does not leak references */
        ff_jni_reset_jfields(env, jfields, jfields_mapping, global, log_ctx);
    }

    return ret;
}