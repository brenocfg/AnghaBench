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
struct Curl_sh_entry {int /*<<< orphan*/  socketp; } ;
struct Curl_multi {int /*<<< orphan*/  sockhash; int /*<<< orphan*/  socket_userp; int /*<<< orphan*/  (* socket_cb ) (struct Curl_easy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct Curl_easy {struct Curl_multi* multi; } ;
typedef  int /*<<< orphan*/  curl_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  CURL_POLL_REMOVE ; 
 int /*<<< orphan*/  sh_delentry (struct Curl_sh_entry*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct Curl_sh_entry* sh_getentry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct Curl_easy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void Curl_multi_closed(struct Curl_easy *data, curl_socket_t s)
{
  if(data) {
    /* if there's still an easy handle associated with this connection */
    struct Curl_multi *multi = data->multi;
    if(multi) {
      /* this is set if this connection is part of a handle that is added to
         a multi handle, and only then this is necessary */
      struct Curl_sh_entry *entry = sh_getentry(&multi->sockhash, s);

      if(entry) {
        if(multi->socket_cb)
          multi->socket_cb(data, s, CURL_POLL_REMOVE,
                           multi->socket_userp,
                           entry->socketp);

        /* now remove it from the socket hash */
        sh_delentry(entry, &multi->sockhash, s);
      }
    }
  }
}