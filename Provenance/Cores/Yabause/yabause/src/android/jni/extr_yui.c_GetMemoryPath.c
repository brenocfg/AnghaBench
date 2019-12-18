#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jstring ;
typedef  int /*<<< orphan*/  jmethodID ;
typedef  int /*<<< orphan*/  jclass ;
typedef  int /*<<< orphan*/  jboolean ;
struct TYPE_10__ {scalar_t__ (* GetEnv ) (TYPE_2__**,void**,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {scalar_t__ (* GetStringLength ) (TYPE_1__**,int /*<<< orphan*/ ) ;char const* (* GetStringUTFChars ) (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* CallObjectMethod ) (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* GetMethodID ) (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ;int /*<<< orphan*/  (* GetObjectClass ) (TYPE_1__**,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 scalar_t__ JNI_OK ; 
 int /*<<< orphan*/  JNI_VERSION_1_6 ; 
 scalar_t__ stub1 (TYPE_2__**,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub5 (TYPE_1__**,int /*<<< orphan*/ ) ; 
 char const* stub6 (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yabause ; 
 TYPE_2__** yvm ; 

const char * GetMemoryPath()
{
    jclass yclass;
    jmethodID getMemoryPath;
    jstring message;
    jboolean dummy;
    JNIEnv * env;
    if ((*yvm)->GetEnv(yvm, (void**) &env, JNI_VERSION_1_6) != JNI_OK)
        return NULL;

    yclass = (*env)->GetObjectClass(env, yabause);
    getMemoryPath = (*env)->GetMethodID(env, yclass, "getMemoryPath", "()Ljava/lang/String;");
    message = (*env)->CallObjectMethod(env, yabause, getMemoryPath);
    if ((*env)->GetStringLength(env, message) == 0)
        return NULL;
    else
        return (*env)->GetStringUTFChars(env, message, &dummy);
}