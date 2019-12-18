#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  jint ;
typedef  scalar_t__ int8_t ;
typedef  enum retro_rumble_effect { ____Placeholder_retro_rumble_effect } retro_rumble_effect ;
struct TYPE_4__ {int /*<<< orphan*/  doVibrate; TYPE_1__* activity; } ;
struct TYPE_3__ {int /*<<< orphan*/  clazz; } ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  CALL_VOID_METHOD_PARAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RETRO_RUMBLE_STRONG ; 
 int RETRO_RUMBLE_WEAK ; 
 TYPE_2__* g_android ; 
 scalar_t__ jni_thread_getenv () ; 

__attribute__((used)) static void android_input_set_rumble_internal(
      uint16_t strength,
      uint16_t *last_strength_strong,
      uint16_t *last_strength_weak,
      uint16_t *last_strength,
      int8_t   id,
      enum retro_rumble_effect effect
      )
{
   JNIEnv *env           = (JNIEnv*)jni_thread_getenv();
   uint16_t new_strength = 0;

   if (!env)
      return;

   if (effect == RETRO_RUMBLE_STRONG)
   {
      new_strength          = strength | *last_strength_weak;
      *last_strength_strong = strength;
   }
   else if (effect == RETRO_RUMBLE_WEAK)
   {
      new_strength         = strength | *last_strength_strong;
      *last_strength_weak  = strength;
   }

   if (new_strength != *last_strength)
   {
      /* trying to send this value as a JNI param without 
       * storing it first was causing 0 to be seen on the other side ?? */
      int strength_final   = (255.0f / 65535.0f) * (float)new_strength;

      CALL_VOID_METHOD_PARAM(env, g_android->activity->clazz,
            g_android->doVibrate, (jint)id, (jint)RETRO_RUMBLE_STRONG, (jint)strength_final, (jint)0);

      *last_strength = new_strength;
   }
}