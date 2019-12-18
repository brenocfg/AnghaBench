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
typedef  int /*<<< orphan*/  copy ;

/* Variables and functions */
 int /*<<< orphan*/  CHEEVOS_LOG (char const*,char const*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static void rcheevos_log_url(const char* format, const char* url)
{
#ifdef CHEEVOS_LOG_URLS
#ifdef CHEEVOS_LOG_PASSWORD
   CHEEVOS_LOG(format, url);
#else
   char copy[256];
   char* aux      = NULL;
   char* next     = NULL;

   if (!string_is_empty(url))
      strlcpy(copy, url, sizeof(copy));

   aux = strstr(copy, "?p=");

   if (!aux)
      aux = strstr(copy, "&p=");

   if (aux)
   {
      aux += 3;
      next = strchr(aux, '&');

      if (next)
      {
         do
         {
            *aux++ = *next++;
         } while (next[-1] != 0);
      }
      else
         *aux = 0;
   }

   aux = strstr(copy, "?t=");

   if (!aux)
      aux = strstr(copy, "&t=");

   if (aux)
   {
      aux += 3;
      next = strchr(aux, '&');

      if (next)
      {
         do
         {
            *aux++ = *next++;
         } while (next[-1] != 0);
      }
      else
         *aux = 0;
   }

   CHEEVOS_LOG(format, copy);
#endif
#else
   (void)format;
   (void)url;
#endif
}