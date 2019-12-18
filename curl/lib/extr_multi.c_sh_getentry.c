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
struct curl_hash {int dummy; } ;
struct Curl_sh_entry {int dummy; } ;
typedef  scalar_t__ curl_socket_t ;

/* Variables and functions */
 scalar_t__ CURL_SOCKET_BAD ; 
 struct Curl_sh_entry* Curl_hash_pick (struct curl_hash*,char*,int) ; 

__attribute__((used)) static struct Curl_sh_entry *sh_getentry(struct curl_hash *sh,
                                         curl_socket_t s)
{
  if(s != CURL_SOCKET_BAD) {
    /* only look for proper sockets */
    return Curl_hash_pick(sh, (char *)&s, sizeof(curl_socket_t));
  }
  return NULL;
}