#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct connectdata {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  connect_only; } ;
struct Curl_easy {TYPE_1__ set; } ;
typedef  scalar_t__ curl_socket_t ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_BAD_FUNCTION_ARGUMENT ; 
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_UNSUPPORTED_PROTOCOL ; 
 scalar_t__ CURL_SOCKET_BAD ; 
 scalar_t__ Curl_getconnectinfo (struct Curl_easy*,struct connectdata**) ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*) ; 

__attribute__((used)) static CURLcode easy_connection(struct Curl_easy *data,
                                curl_socket_t *sfd,
                                struct connectdata **connp)
{
  if(data == NULL)
    return CURLE_BAD_FUNCTION_ARGUMENT;

  /* only allow these to be called on handles with CURLOPT_CONNECT_ONLY */
  if(!data->set.connect_only) {
    failf(data, "CONNECT_ONLY is required!");
    return CURLE_UNSUPPORTED_PROTOCOL;
  }

  *sfd = Curl_getconnectinfo(data, connp);

  if(*sfd == CURL_SOCKET_BAD) {
    failf(data, "Failed to get recent socket");
    return CURLE_UNSUPPORTED_PROTOCOL;
  }

  return CURLE_OK;
}