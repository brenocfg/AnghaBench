#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jfieldID ;
typedef  int /*<<< orphan*/  jclass ;
struct TYPE_7__ {int (* GetStaticIntField ) (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* DeleteLocalRef ) (TYPE_1__**,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* GetStaticFieldID ) (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ;int /*<<< orphan*/  (* FindClass ) (TYPE_1__**,char*) ;} ;
typedef  TYPE_1__* JNIEnv ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  JNI_GET_ENV_OR_RETURN (TYPE_1__**,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__**,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ; 
 int stub3 (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__**,int /*<<< orphan*/ ) ; 

int ff_Build_SDK_INT(AVCodecContext *avctx)
{
    int ret = -1;
    JNIEnv *env = NULL;
    jclass versionClass;
    jfieldID sdkIntFieldID;
    JNI_GET_ENV_OR_RETURN(env, avctx, -1);

    versionClass = (*env)->FindClass(env, "android/os/Build$VERSION");
    sdkIntFieldID = (*env)->GetStaticFieldID(env, versionClass, "SDK_INT", "I");
    ret = (*env)->GetStaticIntField(env, versionClass, sdkIntFieldID);
    (*env)->DeleteLocalRef(env, versionClass);
    return ret;
}