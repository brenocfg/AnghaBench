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
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int strlen (char const*) ; 

__attribute__((used)) static bool duplicate_string( const char *src, char **p_dst )
{
   if (*p_dst)
      free(*p_dst);

   if (src)
   {
      size_t str_size = strlen(src) + 1;

      *p_dst = (char *)malloc(str_size);
      if (!*p_dst)
         return false;

      memcpy(*p_dst, src, str_size);
   } else
      *p_dst = NULL;

   return true;
}