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
struct curl_sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  curlsocktype ;
typedef  int /*<<< orphan*/  curl_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  CURL_SOCKET_BAD ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static curl_socket_t opensocket(void *clientp,
                                curlsocktype purpose,
                                struct curl_sockaddr *address)
{
  (void)purpose;
  (void)address;
  (void)clientp;
  fprintf(stderr, "opensocket() returns CURL_SOCKET_BAD\n");
  return CURL_SOCKET_BAD;
}