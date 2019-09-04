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
typedef  int /*<<< orphan*/  uint8_t ;
struct FFJniField {int type; int /*<<< orphan*/  offset; scalar_t__ name; } ;
typedef  int /*<<< orphan*/ * jmethodID ;
typedef  int /*<<< orphan*/ * jfieldID ;
typedef  int /*<<< orphan*/ * jclass ;
typedef  enum FFJniFieldType { ____Placeholder_FFJniFieldType } FFJniFieldType ;
struct TYPE_5__ {int /*<<< orphan*/  (* DeleteLocalRef ) (TYPE_1__**,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* DeleteGlobalRef ) (TYPE_1__**,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  FF_JNI_CLASS 132 
#define  FF_JNI_FIELD 131 
#define  FF_JNI_METHOD 130 
#define  FF_JNI_STATIC_FIELD 129 
#define  FF_JNI_STATIC_METHOD 128 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__**,int /*<<< orphan*/ *) ; 

int ff_jni_reset_jfields(JNIEnv *env, void *jfields, const struct FFJniField *jfields_mapping, int global, void *log_ctx)
{
    int i;

    for (i = 0; jfields_mapping[i].name; i++) {
        enum FFJniFieldType type = jfields_mapping[i].type;

        switch(type) {
        case FF_JNI_CLASS: {
            jclass clazz = *(jclass*)((uint8_t*)jfields + jfields_mapping[i].offset);
            if (!clazz)
                continue;

            if (global) {
                (*env)->DeleteGlobalRef(env, clazz);
            } else {
                (*env)->DeleteLocalRef(env, clazz);
            }

            *(jclass*)((uint8_t*)jfields + jfields_mapping[i].offset) = NULL;
            break;
        }
        case FF_JNI_FIELD: {
            *(jfieldID*)((uint8_t*)jfields + jfields_mapping[i].offset) = NULL;
            break;
        }
        case FF_JNI_STATIC_FIELD: {
            *(jfieldID*)((uint8_t*)jfields + jfields_mapping[i].offset) = NULL;
            break;
        }
        case FF_JNI_METHOD: {
            *(jmethodID*)((uint8_t*)jfields + jfields_mapping[i].offset) = NULL;
            break;
        }
        case FF_JNI_STATIC_METHOD: {
            *(jmethodID*)((uint8_t*)jfields + jfields_mapping[i].offset) = NULL;
            break;
        }
        default:
            av_log(log_ctx, AV_LOG_ERROR, "Unknown JNI field type\n");
        }
    }

    return 0;
}