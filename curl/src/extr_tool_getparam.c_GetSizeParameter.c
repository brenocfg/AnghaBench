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
struct GlobalConfig {int dummy; } ;
typedef  int curl_off_t ;
typedef  int /*<<< orphan*/  ParameterError ;

/* Variables and functions */
 int CURL_OFF_T_MAX ; 
 int /*<<< orphan*/  PARAM_BAD_USE ; 
 int /*<<< orphan*/  PARAM_NUMBER_TOO_LARGE ; 
 int /*<<< orphan*/  PARAM_OK ; 
 scalar_t__ curlx_strtoofft (char const*,char**,int /*<<< orphan*/ ,int*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  warnf (struct GlobalConfig*,char*,char const*) ; 

__attribute__((used)) static ParameterError GetSizeParameter(struct GlobalConfig *global,
                                       const char *arg,
                                       const char *which,
                                       curl_off_t *value_out)
{
  char *unit;
  curl_off_t value;

  if(curlx_strtoofft(arg, &unit, 0, &value)) {
    warnf(global, "invalid number specified for %s\n", which);
    return PARAM_BAD_USE;
  }

  if(!*unit)
    unit = (char *)"b";
  else if(strlen(unit) > 1)
    unit = (char *)"w"; /* unsupported */

  switch(*unit) {
  case 'G':
  case 'g':
    if(value > (CURL_OFF_T_MAX / (1024*1024*1024)))
      return PARAM_NUMBER_TOO_LARGE;
    value *= 1024*1024*1024;
    break;
  case 'M':
  case 'm':
    if(value > (CURL_OFF_T_MAX / (1024*1024)))
      return PARAM_NUMBER_TOO_LARGE;
    value *= 1024*1024;
    break;
  case 'K':
  case 'k':
    if(value > (CURL_OFF_T_MAX / 1024))
      return PARAM_NUMBER_TOO_LARGE;
    value *= 1024;
    break;
  case 'b':
  case 'B':
    /* for plain bytes, leave as-is */
    break;
  default:
    warnf(global, "unsupported %s unit. Use G, M, K or B!\n", which);
    return PARAM_BAD_USE;
  }
  *value_out = value;
  return PARAM_OK;
}