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
typedef  int /*<<< orphan*/ * gzFile ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * gz_open (char*,int,char const*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

gzFile gzdopen(int fd, const char *mode)
{
   char *path;         /* identifier for error messages */
   gzFile gz;

   if (fd == -1 || (path = (char *)malloc(7 + 3 * sizeof(int))) == NULL)
      return NULL;
#if !defined(NO_snprintf) && !defined(NO_vsnprintf)
   snprintf(path, 7 + 3 * sizeof(int), "<fd:%d>", fd); /* for debugging */
#else
   sprintf(path, "<fd:%d>", fd);   /* for debugging */
#endif
   gz = gz_open(path, fd, mode);
   free(path);
   return gz;
}