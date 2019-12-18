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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int GPE_END_OF_FILE ; 
 int GPE_OK ; 
 int GPE_OUT_OF_MEMORY ; 
 int curlx_uztosi (size_t) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ *) ; 
 char* malloc (int) ; 
 char* realloc (char*,size_t) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static int readline(char **buffer, size_t *bufsize, FILE *stream)
{
  size_t offset = 0;
  char *newptr;

  if(!*buffer) {
    *buffer = malloc(128);
    if(!*buffer)
      return GPE_OUT_OF_MEMORY;
    *bufsize = 128;
  }

  for(;;) {
    size_t length;
    int bytestoread = curlx_uztosi(*bufsize - offset);

    if(!fgets(*buffer + offset, bytestoread, stream))
      return (offset != 0) ? GPE_OK : GPE_END_OF_FILE;

    length = offset + strlen(*buffer + offset);
    if(*(*buffer + length - 1) == '\n')
      break;
    offset = length;
    if(length < *bufsize - 1)
      continue;

    newptr = realloc(*buffer, *bufsize * 2);
    if(!newptr)
      return GPE_OUT_OF_MEMORY;
    *buffer = newptr;
    *bufsize *= 2;
  }

  return GPE_OK;
}