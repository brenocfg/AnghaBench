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
 char* malloc (size_t) ; 

__attribute__((used)) static char *escape_string(const char *src)
{
  size_t bytecount = 0;
  size_t i;
  char *dst;

  for(i = 0; src[i]; i++)
    if(src[i] == '"' || src[i] == '\\')
      bytecount++;

  bytecount += i;
  dst = malloc(bytecount + 1);
  if(!dst)
    return NULL;

  for(i = 0; *src; src++) {
    if(*src == '"' || *src == '\\')
      dst[i++] = '\\';
    dst[i++] = *src;
  }

  dst[i] = '\0';
  return dst;
}