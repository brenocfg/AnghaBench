#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * jobject ;
typedef  int /*<<< orphan*/ * jmethodID ;
typedef  int /*<<< orphan*/  jint ;
typedef  scalar_t__ jclass ;
struct TYPE_9__ {char* (* GetStringUTFChars ) (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ReleaseStringUTFChars ) (TYPE_1__**,int /*<<< orphan*/ *,char const*) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  CALL_OBJ_METHOD (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CALL_OBJ_STATIC_METHOD_PARAM (TYPE_1__**,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIND_CLASS (TYPE_1__**,scalar_t__,char*) ; 
 int /*<<< orphan*/  GET_METHOD_ID (TYPE_1__**,int /*<<< orphan*/ *,scalar_t__,char*,char*) ; 
 int /*<<< orphan*/  GET_STATIC_METHOD_ID (TYPE_1__**,int /*<<< orphan*/ *,scalar_t__,char*,char*) ; 
 int /*<<< orphan*/  RARCH_ERR (char*,int) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,...) ; 
 scalar_t__ jni_thread_getenv () ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 
 char* stub1 (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__**,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static bool android_input_lookup_name_prekitkat(char *buf,
      int *vendorId, int *productId, size_t size, int id)
{
   jobject name      = NULL;
   jmethodID getName = NULL;
   jobject device    = NULL;
   jmethodID method  = NULL;
   jclass    class   = 0;
   const char *str   = NULL;
   JNIEnv     *env   = (JNIEnv*)jni_thread_getenv();

   if (!env)
      goto error;

   RARCH_LOG("Using old lookup");

   FIND_CLASS(env, class, "android/view/InputDevice");
   if (!class)
      goto error;

   GET_STATIC_METHOD_ID(env, method, class, "getDevice",
         "(I)Landroid/view/InputDevice;");
   if (!method)
      goto error;

   CALL_OBJ_STATIC_METHOD_PARAM(env, device, class, method, (jint)id);
   if (!device)
   {
      RARCH_ERR("Failed to find device for ID: %d\n", id);
      goto error;
   }

   GET_METHOD_ID(env, getName, class, "getName", "()Ljava/lang/String;");
   if (!getName)
      goto error;

   CALL_OBJ_METHOD(env, name, device, getName);
   if (!name)
   {
      RARCH_ERR("Failed to find name for device ID: %d\n", id);
      goto error;
   }

   buf[0] = '\0';

   str = (*env)->GetStringUTFChars(env, name, 0);
   if (str)
      strlcpy(buf, str, size);
   (*env)->ReleaseStringUTFChars(env, name, str);

   RARCH_LOG("device name: %s\n", buf);

   return true;
error:
   return false;
}