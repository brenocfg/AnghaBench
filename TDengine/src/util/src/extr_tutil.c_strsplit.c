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
typedef  int int32_t ;

/* Variables and functions */
 int POINTER_BYTES ; 
 char** malloc (int) ; 
 char** realloc (char**,int) ; 
 size_t strlen (char*) ; 
 char* strsep (char**,char const*) ; 

char **strsplit(char *z, const char *delim, int32_t *num) {
  *num = 0;
  int32_t size = 4;

  char **split = malloc(POINTER_BYTES * size);

  for (char *p = strsep(&z, delim); p != NULL; p = strsep(&z, delim)) {
    size_t len = strlen(p);
    if (len == 0) {
      continue;
    }

    split[(*num)++] = p;
    if ((*num) >= size) {
      size = (size << 1);
      split = realloc(split, POINTER_BYTES * size);
    }
  }

  return split;
}