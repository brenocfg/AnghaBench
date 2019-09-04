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
typedef  int CURLSHcode ;

/* Variables and functions */
#define  CURLSHE_BAD_OPTION 134 
#define  CURLSHE_INVALID 133 
#define  CURLSHE_IN_USE 132 
#define  CURLSHE_LAST 131 
#define  CURLSHE_NOMEM 130 
#define  CURLSHE_NOT_BUILT_IN 129 
#define  CURLSHE_OK 128 

const char *
curl_share_strerror(CURLSHcode error)
{
#ifndef CURL_DISABLE_VERBOSE_STRINGS
  switch(error) {
  case CURLSHE_OK:
    return "No error";

  case CURLSHE_BAD_OPTION:
    return "Unknown share option";

  case CURLSHE_IN_USE:
    return "Share currently in use";

  case CURLSHE_INVALID:
    return "Invalid share handle";

  case CURLSHE_NOMEM:
    return "Out of memory";

  case CURLSHE_NOT_BUILT_IN:
    return "Feature not enabled in this library";

  case CURLSHE_LAST:
    break;
  }

  return "CURLSHcode unknown";
#else
  if(error == CURLSHE_OK)
    return "No error";
  else
    return "Error";
#endif
}