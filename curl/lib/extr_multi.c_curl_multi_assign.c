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
struct Curl_sh_entry {void* socketp; } ;
struct Curl_multi {int /*<<< orphan*/  sockhash; scalar_t__ in_callback; } ;
typedef  int /*<<< orphan*/  curl_socket_t ;
typedef  int /*<<< orphan*/  CURLMcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLM_BAD_SOCKET ; 
 int /*<<< orphan*/  CURLM_OK ; 
 int /*<<< orphan*/  CURLM_RECURSIVE_API_CALL ; 
 struct Curl_sh_entry* sh_getentry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

CURLMcode curl_multi_assign(struct Curl_multi *multi, curl_socket_t s,
                            void *hashp)
{
  struct Curl_sh_entry *there = NULL;

  if(multi->in_callback)
    return CURLM_RECURSIVE_API_CALL;

  there = sh_getentry(&multi->sockhash, s);

  if(!there)
    return CURLM_BAD_SOCKET;

  there->socketp = hashp;

  return CURLM_OK;
}