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
typedef  int /*<<< orphan*/  curl_socket_t ;
typedef  int /*<<< orphan*/  CURLcode ;
typedef  int CURLINFO ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_UNKNOWN_OPTION ; 
#define  CURLINFO_ACTIVESOCKET 128 
 int /*<<< orphan*/  Curl_getconnectinfo (struct Curl_easy*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static CURLcode getinfo_socket(struct Curl_easy *data, CURLINFO info,
                               curl_socket_t *param_socketp)
{
  switch(info) {
  case CURLINFO_ACTIVESOCKET:
    *param_socketp = Curl_getconnectinfo(data, NULL);
    break;
  default:
    return CURLE_UNKNOWN_OPTION;
  }

  return CURLE_OK;
}