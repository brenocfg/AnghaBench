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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* wcsdupstr (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static FILE * _wfopen(const wchar_t *wpath, const wchar_t *wmode)
{
   FILE * fd;
   char * path;
   char * mode;

   path = wcsdupstr(wpath);
   if (path == NULL) return NULL;

   mode = wcsdupstr(wmode);
   if (mode == NULL)
   {
      free(path);
      return NULL;
   }

   fd = fopen(path, mode);

   free(path);
   free(mode);

   return fd;
}