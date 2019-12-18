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
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ realloc (char*,size_t) ; 

char* filestream_getline(RFILE *stream)
{
   char *newline_tmp  = NULL;
   size_t cur_size    = 8;
   size_t idx         = 0;
   int in             = 0;
   char *newline      = (char*)malloc(9);

   if (!stream || !newline)
   {
      if (newline)
         free(newline);
      return NULL;
   }

   in                 = filestream_getc(stream);

   while (in != EOF && in != '\n')
   {
      if (idx == cur_size)
      {
         cur_size    *= 2;
         newline_tmp  = (char*)realloc(newline, cur_size + 1);

         if (!newline_tmp)
         {
            free(newline);
            return NULL;
         }

         newline     = newline_tmp;
      }

      newline[idx++] = in;
      in             = filestream_getc(stream);
   }

   newline[idx]      = '\0';
   return newline;
}