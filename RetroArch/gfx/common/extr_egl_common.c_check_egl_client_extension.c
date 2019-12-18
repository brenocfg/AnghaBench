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

/* Variables and functions */
 int /*<<< orphan*/  EGL_EXTENSIONS ; 
 int /*<<< orphan*/  EGL_NO_DISPLAY ; 
 char* eglQueryString (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t strcspn (char const*,char*) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 
 int /*<<< orphan*/  strspn (char const*,char*) ; 

bool check_egl_client_extension(const char *name)
{
   size_t nameLen;
   const char *str = eglQueryString(EGL_NO_DISPLAY, EGL_EXTENSIONS);

   /* The EGL implementation doesn't support client extensions at all. */
   if (!str)
      return false;

   nameLen = strlen(name);
   while (*str != '\0')
   {
      /* Use strspn and strcspn to find the start position and length of each
       * token in the extension string. Using strtok could also work, but
       * that would require allocating a copy of the string. */
      size_t len = strcspn(str, " ");
      if (len == nameLen && strncmp(str, name, nameLen) == 0)
         return true;
      str += len;
      str += strspn(str, " ");
   }

   return false;
}