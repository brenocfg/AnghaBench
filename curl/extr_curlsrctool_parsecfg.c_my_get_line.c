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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_safefree (char*) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 char* realloc (char*,size_t) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strdup (char*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static char *my_get_line(FILE *fp)
{
  char buf[4096];
  char *nl = NULL;
  char *line = NULL;

  do {
    if(NULL == fgets(buf, sizeof(buf), fp))
      break;
    if(!line) {
      line = strdup(buf);
      if(!line)
        return NULL;
    }
    else {
      char *ptr;
      size_t linelen = strlen(line);
      ptr = realloc(line, linelen + strlen(buf) + 1);
      if(!ptr) {
        Curl_safefree(line);
        return NULL;
      }
      line = ptr;
      strcpy(&line[linelen], buf);
    }
    nl = strchr(line, '\n');
  } while(!nl);

  if(nl)
    *nl = '\0';

  return line;
}