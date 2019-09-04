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
struct connectdata {int /*<<< orphan*/ * sock; } ;

/* Variables and functions */
 int CURL_CSELECT_IN ; 
 scalar_t__ Curl_recv_has_postponed_data (struct connectdata*,int) ; 
 scalar_t__ Curl_ssl_data_pending (struct connectdata*,int) ; 
 int SOCKET_READABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool Curl_conn_data_pending(struct connectdata *conn, int sockindex)
{
  int readable;

  if(Curl_ssl_data_pending(conn, sockindex) ||
     Curl_recv_has_postponed_data(conn, sockindex))
    return true;

  readable = SOCKET_READABLE(conn->sock[sockindex], 0);
  return (readable > 0 && (readable & CURL_CSELECT_IN));
}