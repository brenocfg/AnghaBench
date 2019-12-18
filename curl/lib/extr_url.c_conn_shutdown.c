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
struct connectdata {scalar_t__* sock; scalar_t__* tempsock; int /*<<< orphan*/  data; int /*<<< orphan*/  connection_id; } ;

/* Variables and functions */
 scalar_t__ CURL_SOCKET_BAD ; 
 int /*<<< orphan*/  Curl_closesocket (struct connectdata*,scalar_t__) ; 
 int /*<<< orphan*/  Curl_conncache_remove_conn (int /*<<< orphan*/ ,struct connectdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_resolver_cancel (struct connectdata*) ; 
 int /*<<< orphan*/  Curl_ssl_close (struct connectdata*,size_t) ; 
 int /*<<< orphan*/  DEBUGASSERT (int /*<<< orphan*/ ) ; 
 size_t FIRSTSOCKET ; 
 size_t SECONDARYSOCKET ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  infof (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void conn_shutdown(struct connectdata *conn)
{
  if(!conn)
    return;

  infof(conn->data, "Closing connection %ld\n", conn->connection_id);
  DEBUGASSERT(conn->data);

  /* possible left-overs from the async name resolvers */
  Curl_resolver_cancel(conn);

  /* close the SSL stuff before we close any sockets since they will/may
     write to the sockets */
  Curl_ssl_close(conn, FIRSTSOCKET);
  Curl_ssl_close(conn, SECONDARYSOCKET);

  /* close possibly still open sockets */
  if(CURL_SOCKET_BAD != conn->sock[SECONDARYSOCKET])
    Curl_closesocket(conn, conn->sock[SECONDARYSOCKET]);
  if(CURL_SOCKET_BAD != conn->sock[FIRSTSOCKET])
    Curl_closesocket(conn, conn->sock[FIRSTSOCKET]);
  if(CURL_SOCKET_BAD != conn->tempsock[0])
    Curl_closesocket(conn, conn->tempsock[0]);
  if(CURL_SOCKET_BAD != conn->tempsock[1])
    Curl_closesocket(conn, conn->tempsock[1]);

  /* unlink ourselves. this should be called last since other shutdown
     procedures need a valid conn->data and this may clear it. */
  Curl_conncache_remove_conn(conn->data, conn, TRUE);
}