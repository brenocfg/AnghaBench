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
 int FALSE ; 
 int TRUE ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 size_t strlen (char*) ; 

char *Curl_get_line(char *buf, int len, FILE *input)
{
  bool partial = FALSE;
  while(1) {
    char *b = fgets(buf, len, input);
    if(b) {
      size_t rlen = strlen(b);
      if(rlen && (b[rlen-1] == '\n')) {
        if(partial) {
          partial = FALSE;
          continue;
        }
        return b;
      }
      /* read a partial, discard the next piece that ends with newline */
      partial = TRUE;
    }
    else
      break;
  }
  return NULL;
}