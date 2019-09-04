#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct connfind {int /*<<< orphan*/  found; struct connectdata* tofind; } ;
struct connectdata {int /*<<< orphan*/ * sock; struct Curl_easy* data; } ;
struct TYPE_6__ {struct connectdata* lastconnect; } ;
struct Curl_easy {TYPE_3__ state; TYPE_2__* multi; TYPE_1__* multi_easy; } ;
typedef  int /*<<< orphan*/  curl_socket_t ;
struct TYPE_5__ {int /*<<< orphan*/  conn_cache; } ;
struct TYPE_4__ {int /*<<< orphan*/  conn_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURL_SOCKET_BAD ; 
 int /*<<< orphan*/  Curl_conncache_foreach (struct Curl_easy*,int /*<<< orphan*/ *,struct connfind*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUGASSERT (struct Curl_easy*) ; 
 int /*<<< orphan*/  FALSE ; 
 size_t FIRSTSOCKET ; 
 int /*<<< orphan*/  conn_is_conn ; 

curl_socket_t Curl_getconnectinfo(struct Curl_easy *data,
                                  struct connectdata **connp)
{
  DEBUGASSERT(data);

  /* this works for an easy handle:
   * - that has been used for curl_easy_perform()
   * - that is associated with a multi handle, and whose connection
   *   was detached with CURLOPT_CONNECT_ONLY
   */
  if(data->state.lastconnect && (data->multi_easy || data->multi)) {
    struct connectdata *c = data->state.lastconnect;
    struct connfind find;
    find.tofind = data->state.lastconnect;
    find.found = FALSE;

    Curl_conncache_foreach(data, data->multi_easy?
                           &data->multi_easy->conn_cache:
                           &data->multi->conn_cache, &find, conn_is_conn);

    if(!find.found) {
      data->state.lastconnect = NULL;
      return CURL_SOCKET_BAD;
    }

    if(connp) {
      /* only store this if the caller cares for it */
      *connp = c;
      c->data = data;
    }
    return c->sock[FIRSTSOCKET];
  }
  else
    return CURL_SOCKET_BAD;
}