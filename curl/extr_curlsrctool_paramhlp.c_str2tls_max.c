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
typedef  int /*<<< orphan*/  tls_max_array ;
typedef  int /*<<< orphan*/  ParameterError ;

/* Variables and functions */
#define  CURL_SSLVERSION_MAX_DEFAULT 132 
#define  CURL_SSLVERSION_MAX_TLSv1_0 131 
#define  CURL_SSLVERSION_MAX_TLSv1_1 130 
#define  CURL_SSLVERSION_MAX_TLSv1_2 129 
#define  CURL_SSLVERSION_MAX_TLSv1_3 128 
 int /*<<< orphan*/  PARAM_BAD_USE ; 
 int /*<<< orphan*/  PARAM_OK ; 
 int /*<<< orphan*/  PARAM_REQUIRES_PARAMETER ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

ParameterError str2tls_max(long *val, const char *str)
{
   static struct s_tls_max {
    const char *tls_max_str;
    long tls_max;
  } const tls_max_array[] = {
    { "default", CURL_SSLVERSION_MAX_DEFAULT },
    { "1.0",     CURL_SSLVERSION_MAX_TLSv1_0 },
    { "1.1",     CURL_SSLVERSION_MAX_TLSv1_1 },
    { "1.2",     CURL_SSLVERSION_MAX_TLSv1_2 },
    { "1.3",     CURL_SSLVERSION_MAX_TLSv1_3 }
  };
  size_t i = 0;
  if(!str)
    return PARAM_REQUIRES_PARAMETER;
  for(i = 0; i < sizeof(tls_max_array)/sizeof(tls_max_array[0]); i++) {
    if(!strcmp(str, tls_max_array[i].tls_max_str)) {
      *val = tls_max_array[i].tls_max;
      return PARAM_OK;
    }
  }
  return PARAM_BAD_USE;
}