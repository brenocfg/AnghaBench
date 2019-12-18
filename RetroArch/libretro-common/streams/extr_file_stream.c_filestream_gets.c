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
typedef  int /*<<< orphan*/  RFILE ;

/* Variables and functions */
 int EOF ; 
 int filestream_getc (int /*<<< orphan*/ *) ; 

char* filestream_gets(RFILE *stream, char *s, size_t len)
{
   int c   = 0;
   char *p = s;
   if (!stream)
      return NULL;

   /* get max bytes or up to a newline */

   for (len--; len > 0; len--)
   {
      if ((c = filestream_getc(stream)) == EOF)
         break;
      *p++ = c;
      if (c == '\n')
         break;
   }
   *p = 0;

   if (p == s && c == EOF)
      return NULL;
   return (s);
}