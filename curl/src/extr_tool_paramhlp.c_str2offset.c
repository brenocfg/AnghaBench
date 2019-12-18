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
typedef  int /*<<< orphan*/  ParameterError ;
typedef  scalar_t__ CURLofft ;

/* Variables and functions */
 scalar_t__ CURL_OFFT_FLOW ; 
 scalar_t__ CURL_OFFT_INVAL ; 
 scalar_t__ ERANGE ; 
 int /*<<< orphan*/  LONG_MAX ; 
 int /*<<< orphan*/  LONG_MIN ; 
 int /*<<< orphan*/  PARAM_BAD_NUMERIC ; 
 int /*<<< orphan*/  PARAM_NEGATIVE_NUMERIC ; 
 int /*<<< orphan*/  PARAM_NUMBER_TOO_LARGE ; 
 int /*<<< orphan*/  PARAM_OK ; 
 scalar_t__ curlx_strtoofft (char const*,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strtol (char const*,char**,int /*<<< orphan*/ ) ; 

ParameterError str2offset(curl_off_t *val, const char *str)
{
  char *endptr;
  if(str[0] == '-')
    /* offsets aren't negative, this indicates weird input */
    return PARAM_NEGATIVE_NUMERIC;

#if(SIZEOF_CURL_OFF_T > SIZEOF_LONG)
  {
    CURLofft offt = curlx_strtoofft(str, &endptr, 0, val);
    if(CURL_OFFT_FLOW == offt)
      return PARAM_NUMBER_TOO_LARGE;
    else if(CURL_OFFT_INVAL == offt)
      return PARAM_BAD_NUMERIC;
  }
#else
  errno = 0;
  *val = strtol(str, &endptr, 0);
  if((*val == LONG_MIN || *val == LONG_MAX) && errno == ERANGE)
    return PARAM_NUMBER_TOO_LARGE;
#endif
  if((endptr != str) && (endptr == str + strlen(str)))
    return PARAM_OK;

  return PARAM_BAD_NUMERIC;
}