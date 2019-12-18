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
typedef  int /*<<< orphan*/  curl_off_t ;
typedef  int /*<<< orphan*/  CURLofft ;

/* Variables and functions */
 int /*<<< orphan*/  CURL_OFFT_FLOW ; 
 int /*<<< orphan*/  CURL_OFFT_INVAL ; 
 int /*<<< orphan*/  CURL_OFFT_OK ; 
 scalar_t__ ERANGE ; 
 scalar_t__ ISSPACE (char const) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  strtooff (char const*,char**,int) ; 

CURLofft curlx_strtoofft(const char *str, char **endp, int base,
                         curl_off_t *num)
{
  char *end;
  curl_off_t number;
  errno = 0;
  *num = 0; /* clear by default */

  while(*str && ISSPACE(*str))
    str++;
  if('-' == *str) {
    if(endp)
      *endp = (char *)str; /* didn't actually move */
    return CURL_OFFT_INVAL; /* nothing parsed */
  }
  number = strtooff(str, &end, base);
  if(endp)
    *endp = end;
  if(errno == ERANGE)
    /* overflow/underflow */
    return CURL_OFFT_FLOW;
  else if(str == end)
    /* nothing parsed */
    return CURL_OFFT_INVAL;

  *num = number;
  return CURL_OFFT_OK;
}