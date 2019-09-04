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
struct linebuffer {char* buffer; int size; int length; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 scalar_t__ feof (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int getc (int /*<<< orphan*/ *) ; 
 scalar_t__ xrealloc (char*,int) ; 

__attribute__((used)) static struct linebuffer *
readline (struct linebuffer *linebuffer, FILE *stream)
{
  int c;
  char *buffer = linebuffer->buffer;
  char *p = linebuffer->buffer;
  char *end = buffer + linebuffer->size - 1; /* Sentinel. */

  if (feof (stream) || ferror (stream))
    return 0;

  do
    {
      c = getc (stream);
      if (c == EOF)
        {
          if (p == buffer)
            return 0;
          if (p[-1] == '\n')
            break;
          c = '\n';
        }
      if (p == end)
        {
          linebuffer->size *= 2;
          buffer = (char *) xrealloc (buffer, linebuffer->size);
          p = p - linebuffer->buffer + buffer;
          linebuffer->buffer = buffer;
          end = buffer + linebuffer->size - 1;
        }
      *p++ = c;
    }
  while (c != '\n');

  linebuffer->length = p - buffer;
  return linebuffer;
}