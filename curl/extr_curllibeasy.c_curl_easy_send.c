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
struct connectdata {int dummy; } ;
struct Curl_easy {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  curl_socket_t ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_AGAIN ; 
 scalar_t__ CURLE_RECURSIVE_API_CALL ; 
 scalar_t__ CURLE_SEND_ERROR ; 
 scalar_t__ Curl_is_in_callback (struct Curl_easy*) ; 
 scalar_t__ Curl_write (struct connectdata*,int /*<<< orphan*/ ,void const*,size_t,int*) ; 
 scalar_t__ easy_connection (struct Curl_easy*,int /*<<< orphan*/ *,struct connectdata**) ; 

CURLcode curl_easy_send(struct Curl_easy *data, const void *buffer,
                        size_t buflen, size_t *n)
{
  curl_socket_t sfd;
  CURLcode result;
  ssize_t n1;
  struct connectdata *c = NULL;

  if(Curl_is_in_callback(data))
    return CURLE_RECURSIVE_API_CALL;

  result = easy_connection(data, &sfd, &c);
  if(result)
    return result;

  *n = 0;
  result = Curl_write(c, sfd, buffer, buflen, &n1);

  if(n1 == -1)
    return CURLE_SEND_ERROR;

  /* detect EAGAIN */
  if(!result && !n1)
    return CURLE_AGAIN;

  *n = (size_t)n1;

  return result;
}