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
typedef  int ParameterError ;

/* Variables and functions */
#define  PARAM_BAD_NUMERIC 139 
#define  PARAM_BAD_USE 138 
#define  PARAM_GOT_EXTRA_PARAMETER 137 
#define  PARAM_LIBCURL_DOESNT_SUPPORT 136 
#define  PARAM_LIBCURL_UNSUPPORTED_PROTOCOL 135 
#define  PARAM_NEGATIVE_NUMERIC 134 
#define  PARAM_NO_MEM 133 
#define  PARAM_NO_PREFIX 132 
#define  PARAM_NUMBER_TOO_LARGE 131 
#define  PARAM_OPTION_AMBIGUOUS 130 
#define  PARAM_OPTION_UNKNOWN 129 
#define  PARAM_REQUIRES_PARAMETER 128 

const char *param2text(int res)
{
  ParameterError error = (ParameterError)res;
  switch(error) {
  case PARAM_GOT_EXTRA_PARAMETER:
    return "had unsupported trailing garbage";
  case PARAM_OPTION_UNKNOWN:
    return "is unknown";
  case PARAM_OPTION_AMBIGUOUS:
    return "is ambiguous";
  case PARAM_REQUIRES_PARAMETER:
    return "requires parameter";
  case PARAM_BAD_USE:
    return "is badly used here";
  case PARAM_BAD_NUMERIC:
    return "expected a proper numerical parameter";
  case PARAM_NEGATIVE_NUMERIC:
    return "expected a positive numerical parameter";
  case PARAM_LIBCURL_DOESNT_SUPPORT:
    return "the installed libcurl version doesn't support this";
  case PARAM_LIBCURL_UNSUPPORTED_PROTOCOL:
    return "a specified protocol is unsupported by libcurl";
  case PARAM_NO_MEM:
    return "out of memory";
  case PARAM_NO_PREFIX:
    return "the given option can't be reversed with a --no- prefix";
  case PARAM_NUMBER_TOO_LARGE:
    return "too large number";
  default:
    return "unknown error";
  }
}