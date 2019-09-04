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
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_auth_create_login_message (struct Curl_easy*,char const*,char**,size_t*) ; 

CURLcode Curl_auth_create_external_message(struct Curl_easy *data,
                                           const char *user, char **outptr,
                                           size_t *outlen)
{
  /* This is the same formatting as the login message */
  return Curl_auth_create_login_message(data, user, outptr, outlen);
}