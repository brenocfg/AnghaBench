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
 int /*<<< orphan*/  Curl_safefree (char*) ; 
 scalar_t__ Curl_urldecode (struct Curl_easy*,char const*,size_t,char**,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ INT_MAX ; 
 int curlx_uztosi (size_t) ; 

char *curl_easy_unescape(struct Curl_easy *data, const char *string,
                         int length, int *olen)
{
  char *str = NULL;
  if(length >= 0) {
    size_t inputlen = length;
    size_t outputlen;
    CURLcode res = Curl_urldecode(data, string, inputlen, &str, &outputlen,
                                  FALSE);
    if(res)
      return NULL;

    if(olen) {
      if(outputlen <= (size_t) INT_MAX)
        *olen = curlx_uztosi(outputlen);
      else
        /* too large to return in an int, fail! */
        Curl_safefree(str);
    }
  }
  return str;
}