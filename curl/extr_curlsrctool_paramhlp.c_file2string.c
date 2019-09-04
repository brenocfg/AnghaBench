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
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 char* realloc (char*,size_t) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char*) ; 

ParameterError file2string(char **bufp, FILE *file)
{
  char *ptr;
  char *string = NULL;

  if(file) {
    char buffer[256];
    size_t stringlen = 0;
    while(fgets(buffer, sizeof(buffer), file)) {
      size_t buflen;
      ptr = strchr(buffer, '\r');
      if(ptr)
        *ptr = '\0';
      ptr = strchr(buffer, '\n');
      if(ptr)
        *ptr = '\0';
      buflen = strlen(buffer);
      ptr = realloc(string, stringlen + buflen + 1);
      if(!ptr) {
        Curl_safefree(string);
        return PARAM_NO_MEM;
      }
      string = ptr;
      strcpy(string + stringlen, buffer);
      stringlen += buflen;
    }
  }
  *bufp = string;
  return PARAM_OK;
}