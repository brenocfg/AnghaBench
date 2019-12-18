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
 int /*<<< orphan*/  memmove (char*,char*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void vc_uri_remove_single_dot_segments( char *path_str )
{
   char *slash = path_str - 1;

   while (slash++)
   {
      if (*slash == '.')
      {
         switch (slash[1])
         {
         case '/':   /* Single dot segment, remove it */
            memmove(slash, slash + 2, strlen(slash + 2) + 1);
            break;
         case '\0':  /* Trailing single dot, remove it */
            *slash = '\0';
            break;
         default:    /* Something else (e.g. ".." or ".foo") */
            ;  /* Do nothing */
         }
      }
      slash = strchr(slash, '/');
   }
}