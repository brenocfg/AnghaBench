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
typedef  scalar_t__ jclass ;
struct TYPE_6__ {int /*<<< orphan*/  (* DeleteLocalRef ) (TYPE_1__**,scalar_t__) ;int /*<<< orphan*/  (* ThrowNew ) (TYPE_1__**,scalar_t__,char const*) ;scalar_t__ (* FindClass ) (TYPE_1__**,char const*) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 scalar_t__ stub1 (TYPE_1__**,char const*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__**,scalar_t__,char const*) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__**,scalar_t__) ; 

__attribute__((used)) static inline void
throw_exc(JNIEnv *env,
          const char *name,
          const char *msg)
{
    jclass cls = (*env)->FindClass(env, name);
    if(cls)
        (*env)->ThrowNew(env, cls, msg);
    (*env)->DeleteLocalRef(env, cls);
}