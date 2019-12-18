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
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/  ParameterError ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_safefree (char*) ; 
 int /*<<< orphan*/  PARAM_NO_MEM ; 
 int /*<<< orphan*/  PARAM_OK ; 
 scalar_t__ SIZE_T_MAX ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 char* malloc (size_t) ; 
 char* realloc (char*,size_t) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char*) ; 

ParameterError file2string(char **bufp, FILE *file)
{
  char *string = NULL;
  if(file) {
    char *ptr;
    size_t alloc = 512;
    size_t alloc_needed;
    char buffer[256];
    size_t stringlen = 0;
    string = malloc(alloc);
    if(!string)
      return PARAM_NO_MEM;

    while(fgets(buffer, sizeof(buffer), file)) {
      size_t buflen;
      ptr = strchr(buffer, '\r');
      if(ptr)
        *ptr = '\0';
      ptr = strchr(buffer, '\n');
      if(ptr)
        *ptr = '\0';
      buflen = strlen(buffer);
      alloc_needed = stringlen + buflen + 1;
      if(alloc < alloc_needed) {
#if SIZEOF_SIZE_T < 8
        if(alloc >= (size_t)SIZE_T_MAX/2) {
          Curl_safefree(string);
          return PARAM_NO_MEM;
        }
#endif
        /* doubling is enough since the string to add is always max 256 bytes
           and the alloc size start at 512 */
        alloc *= 2;
        ptr = realloc(string, alloc);
        if(!ptr) {
          Curl_safefree(string);
          return PARAM_NO_MEM;
        }
        string = ptr;
      }
      strcpy(string + stringlen, buffer);
      stringlen += buflen;
    }
  }
  *bufp = string;
  return PARAM_OK;
}