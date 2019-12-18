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
typedef  int /*<<< orphan*/  curl_socket_t ;
typedef  scalar_t__ CURLMcode ;
typedef  int /*<<< orphan*/  CURLM ;

/* Variables and functions */
 scalar_t__ CURLM_OK ; 
 scalar_t__ curl_multi_socket_action (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 
 char* curl_multi_strerror (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,scalar_t__,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void notifyCurl(CURLM *curl, curl_socket_t s, int evBitmask,
                       const char *info)
{
  int numhandles = 0;
  CURLMcode result = curl_multi_socket_action(curl, s, evBitmask, &numhandles);
  if(result != CURLM_OK) {
    fprintf(stderr, "Curl error on %s: %i (%s)\n",
            info, result, curl_multi_strerror(result));
  }
}