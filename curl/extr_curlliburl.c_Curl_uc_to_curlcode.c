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
typedef  int /*<<< orphan*/  CURLcode ;
typedef  int CURLUcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_LOGIN_DENIED ; 
 int /*<<< orphan*/  CURLE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  CURLE_UNSUPPORTED_PROTOCOL ; 
 int /*<<< orphan*/  CURLE_URL_MALFORMAT ; 
#define  CURLUE_OUT_OF_MEMORY 130 
#define  CURLUE_UNSUPPORTED_SCHEME 129 
#define  CURLUE_USER_NOT_ALLOWED 128 

CURLcode Curl_uc_to_curlcode(CURLUcode uc)
{
  switch(uc) {
  default:
    return CURLE_URL_MALFORMAT;
  case CURLUE_UNSUPPORTED_SCHEME:
    return CURLE_UNSUPPORTED_PROTOCOL;
  case CURLUE_OUT_OF_MEMORY:
    return CURLE_OUT_OF_MEMORY;
  case CURLUE_USER_NOT_ALLOWED:
    return CURLE_LOGIN_DENIED;
  }
}