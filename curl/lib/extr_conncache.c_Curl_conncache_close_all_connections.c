#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct connectdata {TYPE_2__* data; } ;
struct conncache {TYPE_2__* closure_handle; } ;
struct TYPE_6__ {int /*<<< orphan*/  hostcache; } ;
struct TYPE_7__ {TYPE_1__ dns; } ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_close (TYPE_2__**) ; 
 int /*<<< orphan*/  Curl_disconnect (TYPE_2__*,struct connectdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_hostcache_clean (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SIGPIPE_VARIABLE (int /*<<< orphan*/ ) ; 
 struct connectdata* conncache_find_first_connection (struct conncache*) ; 
 int /*<<< orphan*/  connclose (struct connectdata*,char*) ; 
 int /*<<< orphan*/  pipe_st ; 
 int /*<<< orphan*/  sigpipe_ignore (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigpipe_restore (int /*<<< orphan*/ *) ; 

void Curl_conncache_close_all_connections(struct conncache *connc)
{
  struct connectdata *conn;

  conn = conncache_find_first_connection(connc);
  while(conn) {
    SIGPIPE_VARIABLE(pipe_st);
    conn->data = connc->closure_handle;

    sigpipe_ignore(conn->data, &pipe_st);
    /* This will remove the connection from the cache */
    connclose(conn, "kill all");
    (void)Curl_disconnect(connc->closure_handle, conn, FALSE);
    sigpipe_restore(&pipe_st);

    conn = conncache_find_first_connection(connc);
  }

  if(connc->closure_handle) {
    SIGPIPE_VARIABLE(pipe_st);
    sigpipe_ignore(connc->closure_handle, &pipe_st);

    Curl_hostcache_clean(connc->closure_handle,
                         connc->closure_handle->dns.hostcache);
    Curl_close(&connc->closure_handle);
    sigpipe_restore(&pipe_st);
  }
}