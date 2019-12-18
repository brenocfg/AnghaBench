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
typedef  int /*<<< orphan*/  jobject ;
struct TYPE_13__ {int /*<<< orphan*/  get_name_id; } ;
struct TYPE_15__ {TYPE_1__ jfields; int /*<<< orphan*/  object; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* DeleteLocalRef ) (TYPE_2__**,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* CallObjectMethod ) (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__* JNIEnv ;
typedef  TYPE_3__ FFAMediaCodec ;

/* Variables and functions */
 int /*<<< orphan*/  JNI_GET_ENV_OR_RETURN (TYPE_2__**,TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ff_jni_exception_check (TYPE_2__**,int,TYPE_3__*) ; 
 char* ff_jni_jstring_to_utf_chars (TYPE_2__**,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/ * stub1 (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__**,int /*<<< orphan*/ *) ; 

char *ff_AMediaCodec_getName(FFAMediaCodec *codec)
{
    char *ret = NULL;
    JNIEnv *env = NULL;
    jobject *name = NULL;

    JNI_GET_ENV_OR_RETURN(env, codec, NULL);

    name = (*env)->CallObjectMethod(env, codec->object, codec->jfields.get_name_id);
    if (ff_jni_exception_check(env, 1, codec) < 0) {
        goto fail;
    }

    ret = ff_jni_jstring_to_utf_chars(env, name, codec);

fail:
    if (name) {
        (*env)->DeleteLocalRef(env, name);
    }

    return ret;
}