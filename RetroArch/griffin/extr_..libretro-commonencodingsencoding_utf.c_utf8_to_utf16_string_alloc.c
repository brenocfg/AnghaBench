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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  CP_UTF8 ; 
 size_t MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ calloc (size_t,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int mbstowcs (int /*<<< orphan*/ *,char const*,size_t) ; 

wchar_t* utf8_to_utf16_string_alloc(const char *str)
{
#ifdef _WIN32
   int len = 0;
   int out_len = 0;
#else
   size_t len = 0;
   size_t out_len = 0;
#endif
   wchar_t *buf = NULL;

   if (!str || !*str)
      return NULL;

#ifdef _WIN32
   len = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);

   if (len)
   {
      buf = (wchar_t*)calloc(len, sizeof(wchar_t));

      if (!buf)
         return NULL;

      out_len = MultiByteToWideChar(CP_UTF8, 0, str, -1, buf, len);
   }
   else
   {
      /* fallback to ANSI codepage instead */
      len = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);

      if (len)
      {
         buf = (wchar_t*)calloc(len, sizeof(wchar_t));

         if (!buf)
            return NULL;

         out_len = MultiByteToWideChar(CP_ACP, 0, str, -1, buf, len);
      }
   }

   if (out_len < 0)
   {
      free(buf);
      return NULL;
   }
#else
   /* NOTE: For now, assume non-Windows platforms' locale is already UTF-8. */
   len = mbstowcs(NULL, str, 0) + 1;

   if (len)
   {
      buf = (wchar_t*)calloc(len, sizeof(wchar_t));

      if (!buf)
         return NULL;

      out_len = mbstowcs(buf, str, len);
   }

   if (out_len == (size_t)-1)
   {
      free(buf);
      return NULL;
   }
#endif

   return buf;
}