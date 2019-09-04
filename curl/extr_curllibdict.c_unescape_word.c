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
struct Curl_easy {int dummy; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ Curl_urldecode (struct Curl_easy*,char const*,int /*<<< orphan*/ ,char**,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 

__attribute__((used)) static char *unescape_word(struct Curl_easy *data, const char *inputbuff)
{
  char *newp = NULL;
  char *dictp;
  size_t len;

  CURLcode result = Curl_urldecode(data, inputbuff, 0, &newp, &len, FALSE);
  if(!newp || result)
    return NULL;

  dictp = malloc(len*2 + 1); /* add one for terminating zero */
  if(dictp) {
    char *ptr;
    char ch;
    int olen = 0;
    /* According to RFC2229 section 2.2, these letters need to be escaped with
       \[letter] */
    for(ptr = newp;
        (ch = *ptr) != 0;
        ptr++) {
      if((ch <= 32) || (ch == 127) ||
          (ch == '\'') || (ch == '\"') || (ch == '\\')) {
        dictp[olen++] = '\\';
      }
      dictp[olen++] = ch;
    }
    dictp[olen] = 0;
  }
  free(newp);
  return dictp;
}