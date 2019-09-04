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
typedef  size_t ssize_t ;
typedef  scalar_t__ curl_socket_t ;
typedef  scalar_t__ CURLcode ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  CURLINFO_LASTSOCKET ; 
 scalar_t__ CURL_SOCKET_BAD ; 
 int /*<<< orphan*/  TEST_ERR_MAJOR_BAD ; 
 int* counter ; 
 scalar_t__ curl_easy_getinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,long*) ; 
 char* curl_easy_strerror (scalar_t__) ; 
 int curlx_sztosi (size_t) ; 
 int /*<<< orphan*/ ** easy ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  res ; 
 scalar_t__* sockets ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static size_t callback(char *ptr, size_t size, size_t nmemb, void *data)
{
  ssize_t idx = ((CURL **) data) - easy;
  curl_socket_t sock;
  long longdata;
  CURLcode code;
  const size_t failure = (size && nmemb) ? 0 : 1;
  (void)ptr;

  counter[idx] += (int)(size * nmemb);

  /* Get socket being used for this easy handle, otherwise CURL_SOCKET_BAD */
  code = curl_easy_getinfo(easy[idx], CURLINFO_LASTSOCKET, &longdata);
  if(CURLE_OK != code) {
    fprintf(stderr, "%s:%d curl_easy_getinfo() failed, "
            "with code %d (%s)\n",
            __FILE__, __LINE__, (int)code, curl_easy_strerror(code));
    res = TEST_ERR_MAJOR_BAD;
    return failure;
  }
  if(longdata == -1L)
    sock = CURL_SOCKET_BAD;
  else
    sock = (curl_socket_t)longdata;

  if(sock != CURL_SOCKET_BAD) {
    /* Track relationship between this easy handle and the socket. */
    if(sockets[idx] == CURL_SOCKET_BAD) {
      /* An easy handle without previous socket, record the socket. */
      sockets[idx] = sock;
    }
    else if(sock != sockets[idx]) {
      /* An easy handle with a socket different to previously
         tracked one, log and fail right away. Known bug #37. */
      fprintf(stderr, "Handle %d started on socket %d and moved to %d\n",
              curlx_sztosi(idx), (int)sockets[idx], (int)sock);
      res = TEST_ERR_MAJOR_BAD;
      return failure;
    }
  }
  return size * nmemb;
}