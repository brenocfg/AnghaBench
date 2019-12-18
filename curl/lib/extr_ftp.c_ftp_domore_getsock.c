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
struct ftp_conn {scalar_t__ state; int /*<<< orphan*/  pp; } ;
struct TYPE_6__ {struct ftp_conn ftpc; } ;
struct connectdata {scalar_t__* sock; scalar_t__* tempsock; TYPE_3__ proto; TYPE_2__* data; } ;
typedef  scalar_t__ curl_socket_t ;
struct TYPE_4__ {int /*<<< orphan*/  ftp_use_port; } ;
struct TYPE_5__ {TYPE_1__ set; } ;

/* Variables and functions */
 scalar_t__ CURL_SOCKET_BAD ; 
 int Curl_pp_getsock (int /*<<< orphan*/ *,scalar_t__*) ; 
 size_t FIRSTSOCKET ; 
 scalar_t__ FTP_STOP ; 
 int GETSOCK_READSOCK (int) ; 
 int GETSOCK_WRITESOCK (int) ; 
 size_t SECONDARYSOCKET ; 

__attribute__((used)) static int ftp_domore_getsock(struct connectdata *conn, curl_socket_t *socks)
{
  struct ftp_conn *ftpc = &conn->proto.ftpc;

  /* When in DO_MORE state, we could be either waiting for us to connect to a
   * remote site, or we could wait for that site to connect to us. Or just
   * handle ordinary commands.
   */

  if(FTP_STOP == ftpc->state) {
    int bits = GETSOCK_READSOCK(0);

    /* if stopped and still in this state, then we're also waiting for a
       connect on the secondary connection */
    socks[0] = conn->sock[FIRSTSOCKET];

    if(!conn->data->set.ftp_use_port) {
      int s;
      int i;
      /* PORT is used to tell the server to connect to us, and during that we
         don't do happy eyeballs, but we do if we connect to the server */
      for(s = 1, i = 0; i<2; i++) {
        if(conn->tempsock[i] != CURL_SOCKET_BAD) {
          socks[s] = conn->tempsock[i];
          bits |= GETSOCK_WRITESOCK(s++);
        }
      }
    }
    else {
      socks[1] = conn->sock[SECONDARYSOCKET];
      bits |= GETSOCK_WRITESOCK(1) | GETSOCK_READSOCK(1);
    }

    return bits;
  }
  return Curl_pp_getsock(&conn->proto.ftpc.pp, socks);
}