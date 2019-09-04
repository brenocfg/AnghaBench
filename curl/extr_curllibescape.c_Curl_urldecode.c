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
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  CURLE_URL_MALFORMAT ; 
 int /*<<< orphan*/  Curl_convert_from_network (struct Curl_easy*,char*,int) ; 
 scalar_t__ ISXDIGIT (char const) ; 
 unsigned char curlx_ultouc (unsigned long) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 size_t strlen (char const*) ; 
 unsigned long strtoul (char*,char**,int) ; 

CURLcode Curl_urldecode(struct Curl_easy *data,
                        const char *string, size_t length,
                        char **ostring, size_t *olen,
                        bool reject_ctrl)
{
  size_t alloc = (length?length:strlen(string)) + 1;
  char *ns = malloc(alloc);
  size_t strindex = 0;
  unsigned long hex;
  CURLcode result = CURLE_OK;

  if(!ns)
    return CURLE_OUT_OF_MEMORY;

  while(--alloc > 0) {
    unsigned char in = *string;
    if(('%' == in) && (alloc > 2) &&
       ISXDIGIT(string[1]) && ISXDIGIT(string[2])) {
      /* this is two hexadecimal digits following a '%' */
      char hexstr[3];
      char *ptr;
      hexstr[0] = string[1];
      hexstr[1] = string[2];
      hexstr[2] = 0;

      hex = strtoul(hexstr, &ptr, 16);

      in = curlx_ultouc(hex); /* this long is never bigger than 255 anyway */

      if(data) {
        result = Curl_convert_from_network(data, (char *)&in, 1);
        if(result) {
          /* Curl_convert_from_network calls failf if unsuccessful */
          free(ns);
          return result;
        }
      }

      string += 2;
      alloc -= 2;
    }

    if(reject_ctrl && (in < 0x20)) {
      free(ns);
      return CURLE_URL_MALFORMAT;
    }

    ns[strindex++] = in;
    string++;
  }
  ns[strindex] = 0; /* terminate it */

  if(olen)
    /* store output size */
    *olen = strindex;

  /* store output string */
  *ostring = ns;

  return CURLE_OK;
}