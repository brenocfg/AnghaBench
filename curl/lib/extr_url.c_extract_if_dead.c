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
struct curltime {int dummy; } ;
struct connectdata {int /*<<< orphan*/  connection_id; int /*<<< orphan*/ * sock; struct Curl_easy* data; TYPE_1__* handler; } ;
struct Curl_easy {int dummy; } ;
struct TYPE_2__ {unsigned int (* connection_check ) (struct connectdata*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CONNCHECK_ISDEAD ; 
 unsigned int CONNRESULT_DEAD ; 
 int /*<<< orphan*/  CONN_INUSE (struct connectdata*) ; 
 int /*<<< orphan*/  Curl_conncache_remove_conn (struct Curl_easy*,struct connectdata*,int) ; 
 struct curltime Curl_now () ; 
 int FALSE ; 
 size_t FIRSTSOCKET ; 
 int SocketIsDead (int /*<<< orphan*/ ) ; 
 int TRUE ; 
 scalar_t__ conn_maxage (struct Curl_easy*,struct connectdata*,struct curltime) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,int /*<<< orphan*/ ) ; 
 unsigned int stub1 (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool extract_if_dead(struct connectdata *conn,
                            struct Curl_easy *data)
{
  if(!CONN_INUSE(conn) && !conn->data) {
    /* The check for a dead socket makes sense only if the connection isn't in
       use */
    bool dead;
    struct curltime now = Curl_now();
    if(conn_maxage(data, conn, now)) {
      dead = TRUE;
    }
    else if(conn->handler->connection_check) {
      /* The protocol has a special method for checking the state of the
         connection. Use it to check if the connection is dead. */
      unsigned int state;
      struct Curl_easy *olddata = conn->data;
      conn->data = data; /* use this transfer for now */
      state = conn->handler->connection_check(conn, CONNCHECK_ISDEAD);
      conn->data = olddata;
      dead = (state & CONNRESULT_DEAD);
    }
    else {
      /* Use the general method for determining the death of a connection */
      dead = SocketIsDead(conn->sock[FIRSTSOCKET]);
    }

    if(dead) {
      infof(data, "Connection %ld seems to be dead!\n", conn->connection_id);
      Curl_conncache_remove_conn(data, conn, FALSE);
      return TRUE;
    }
  }
  return FALSE;
}