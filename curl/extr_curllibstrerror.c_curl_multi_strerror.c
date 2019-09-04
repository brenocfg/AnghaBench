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
typedef  int CURLMcode ;

/* Variables and functions */
#define  CURLM_ADDED_ALREADY 138 
#define  CURLM_BAD_EASY_HANDLE 137 
#define  CURLM_BAD_HANDLE 136 
#define  CURLM_BAD_SOCKET 135 
#define  CURLM_CALL_MULTI_PERFORM 134 
#define  CURLM_INTERNAL_ERROR 133 
#define  CURLM_LAST 132 
#define  CURLM_OK 131 
#define  CURLM_OUT_OF_MEMORY 130 
#define  CURLM_RECURSIVE_API_CALL 129 
#define  CURLM_UNKNOWN_OPTION 128 

const char *
curl_multi_strerror(CURLMcode error)
{
#ifndef CURL_DISABLE_VERBOSE_STRINGS
  switch(error) {
  case CURLM_CALL_MULTI_PERFORM:
    return "Please call curl_multi_perform() soon";

  case CURLM_OK:
    return "No error";

  case CURLM_BAD_HANDLE:
    return "Invalid multi handle";

  case CURLM_BAD_EASY_HANDLE:
    return "Invalid easy handle";

  case CURLM_OUT_OF_MEMORY:
    return "Out of memory";

  case CURLM_INTERNAL_ERROR:
    return "Internal error";

  case CURLM_BAD_SOCKET:
    return "Invalid socket argument";

  case CURLM_UNKNOWN_OPTION:
    return "Unknown option";

  case CURLM_ADDED_ALREADY:
    return "The easy handle is already added to a multi handle";

  case CURLM_RECURSIVE_API_CALL:
    return "API function called from within callback";

  case CURLM_LAST:
    break;
  }

  return "Unknown error";
#else
  if(error == CURLM_OK)
    return "No error";
  else
    return "Error";
#endif
}