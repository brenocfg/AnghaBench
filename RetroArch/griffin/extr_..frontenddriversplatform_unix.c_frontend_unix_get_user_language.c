#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * jstring ;
typedef  enum retro_language { ____Placeholder_retro_language } retro_language ;
struct TYPE_10__ {scalar_t__ getUserLanguageString; TYPE_1__* activity; } ;
struct TYPE_9__ {char* (* GetStringUTFChars ) (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ReleaseStringUTFChars ) (TYPE_2__**,int /*<<< orphan*/ *,char const*) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  clazz; } ;
typedef  TYPE_2__* JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  CALL_OBJ_METHOD (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int RETRO_LANGUAGE_ENGLISH ; 
 TYPE_6__* g_android ; 
 char* getenv (char*) ; 
 TYPE_2__** jni_thread_getenv () ; 
 int rarch_get_language_from_iso (char const*) ; 
 char* stub1 (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__**,int /*<<< orphan*/ *,char const*) ; 

enum retro_language frontend_unix_get_user_language(void)
{
   enum retro_language lang = RETRO_LANGUAGE_ENGLISH;
#ifdef HAVE_LANGEXTRA
#ifdef ANDROID
   jstring jstr = NULL;
   JNIEnv *env = jni_thread_getenv();

   if (!env || !g_android)
      return lang;

   if (g_android->getUserLanguageString)
   {
      CALL_OBJ_METHOD(env, jstr,
            g_android->activity->clazz, g_android->getUserLanguageString);

      if (jstr)
      {
         const char *langStr = (*env)->GetStringUTFChars(env, jstr, 0);

         lang = rarch_get_language_from_iso(langStr);

         (*env)->ReleaseStringUTFChars(env, jstr, langStr);
      }
   }
#else
   char *envvar = getenv("LANG");

   if (envvar != NULL)
      lang = rarch_get_language_from_iso(envvar);
#endif
#endif
   return lang;
}