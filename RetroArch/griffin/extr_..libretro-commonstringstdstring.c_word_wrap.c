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
 scalar_t__ strlen (char const*) ; 
 char* utf8skip (char const*,int) ; 

char *word_wrap(char* buffer, const char *string, int line_width, bool unicode, unsigned max_lines)
{
   unsigned i     = 0;
   unsigned len   = (unsigned)strlen(string);
   unsigned lines = 1;

   while (i < len)
   {
      unsigned counter;
      int pos = (int)(&buffer[i] - buffer);

      /* copy string until the end of the line is reached */
      for (counter = 1; counter <= (unsigned)line_width; counter++)
      {
         const char *character;
         unsigned char_len;
         unsigned j = i;

         /* check if end of string reached */
         if (i == len)
         {
            buffer[i] = 0;
            return buffer;
         }

         character = utf8skip(&string[i], 1);
         char_len  = (unsigned)(character - &string[i]);

         if (!unicode)
            counter += char_len - 1;

         do
         {
            buffer[i] = string[i];
            char_len--;
            i++;
         } while(char_len);

         /* check for newlines embedded in the original input
          * and reset the index */
         if (buffer[j] == '\n')
         {
            lines++;
            counter = 1;
         }
      }

      /* check for whitespace */
      if (string[i] == ' ')
      {
         if ((max_lines == 0 || lines < max_lines))
         {
            buffer[i] = '\n';
            i++;
            lines++;
         }
      }
      else
      {
         int k;

         /* check for nearest whitespace back in string */
         for (k = i; k > 0; k--)
         {
            if (string[k] != ' ' || (max_lines != 0 && lines >= max_lines))
               continue;

            buffer[k] = '\n';
            /* set string index back to character after this one */
            i         = k + 1;
            lines++;
            break;
         }

         if (&buffer[i] - buffer == pos)
            return buffer;
      }
   }

   buffer[i] = 0;

   return buffer;
}