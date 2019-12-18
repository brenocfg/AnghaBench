#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  enum retro_language { ____Placeholder_retro_language } retro_language ;
typedef  int /*<<< orphan*/  LANGID ;

/* Variables and functions */
 int /*<<< orphan*/  GetUserDefaultUILanguage () ; 
 int RETRO_LANGUAGE_ENGLISH ; 
 int win32_get_retro_lang_from_langid (int /*<<< orphan*/ ) ; 

enum retro_language frontend_win32_get_user_language(void)
{
   enum retro_language lang = RETRO_LANGUAGE_ENGLISH;
#if defined(HAVE_LANGEXTRA) && !defined(_XBOX)
#if (defined(_WIN32_WINNT) && _WIN32_WINNT >= 0x0500) || !defined(_MSC_VER)
   LANGID langid = GetUserDefaultUILanguage();
   lang = win32_get_retro_lang_from_langid(langid);
#endif
#endif
   return lang;
}