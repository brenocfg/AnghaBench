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
struct connectdata {int /*<<< orphan*/  connect_state; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CONNECT (struct connectdata*,int,char const*,int) ; 
 scalar_t__ Curl_connect_complete (struct connectdata*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  connect_done (struct connectdata*) ; 
 scalar_t__ connect_init (struct connectdata*,int /*<<< orphan*/ ) ; 

CURLcode Curl_proxyCONNECT(struct connectdata *conn,
                           int sockindex,
                           const char *hostname,
                           int remote_port)
{
  CURLcode result;
  if(!conn->connect_state) {
    result = connect_init(conn, FALSE);
    if(result)
      return result;
  }
  result = CONNECT(conn, sockindex, hostname, remote_port);

  if(result || Curl_connect_complete(conn))
    connect_done(conn);

  return result;
}