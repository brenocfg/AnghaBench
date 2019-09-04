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
struct pingpong {scalar_t__ sendthis; scalar_t__ sendsize; scalar_t__ sendleft; int /*<<< orphan*/  response; struct connectdata* conn; } ;
struct connectdata {int /*<<< orphan*/ * sock; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  curl_socket_t ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  Curl_now () ; 
 scalar_t__ Curl_write (struct connectdata*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__*) ; 
 size_t FIRSTSOCKET ; 
 int /*<<< orphan*/  free (scalar_t__) ; 

CURLcode Curl_pp_flushsend(struct pingpong *pp)
{
  /* we have a piece of a command still left to send */
  struct connectdata *conn = pp->conn;
  ssize_t written;
  curl_socket_t sock = conn->sock[FIRSTSOCKET];
  CURLcode result = Curl_write(conn, sock, pp->sendthis + pp->sendsize -
                               pp->sendleft, pp->sendleft, &written);
  if(result)
    return result;

  if(written != (ssize_t)pp->sendleft) {
    /* only a fraction was sent */
    pp->sendleft -= written;
  }
  else {
    free(pp->sendthis);
    pp->sendthis = NULL;
    pp->sendleft = pp->sendsize = 0;
    pp->response = Curl_now();
  }
  return CURLE_OK;
}