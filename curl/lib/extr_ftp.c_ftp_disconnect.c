#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pingpong {int dummy; } ;
struct ftp_conn {int /*<<< orphan*/ * server_os; int /*<<< orphan*/ * prevpath; int /*<<< orphan*/ * entrypath; int /*<<< orphan*/  ctl_valid; struct pingpong pp; } ;
struct TYPE_3__ {struct ftp_conn ftpc; } ;
struct connectdata {struct Curl_easy* data; TYPE_1__ proto; } ;
struct TYPE_4__ {int /*<<< orphan*/ * most_recent_ftp_entrypath; } ;
struct Curl_easy {TYPE_2__ state; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  Curl_pp_disconnect (struct pingpong*) ; 
 int /*<<< orphan*/  Curl_sec_end (struct connectdata*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freedirs (struct ftp_conn*) ; 
 int /*<<< orphan*/  ftp_quit (struct connectdata*) ; 

__attribute__((used)) static CURLcode ftp_disconnect(struct connectdata *conn, bool dead_connection)
{
  struct ftp_conn *ftpc = &conn->proto.ftpc;
  struct pingpong *pp = &ftpc->pp;

  /* We cannot send quit unconditionally. If this connection is stale or
     bad in any way, sending quit and waiting around here will make the
     disconnect wait in vain and cause more problems than we need to.

     ftp_quit() will check the state of ftp->ctl_valid. If it's ok it
     will try to send the QUIT command, otherwise it will just return.
  */
  if(dead_connection)
    ftpc->ctl_valid = FALSE;

  /* The FTP session may or may not have been allocated/setup at this point! */
  (void)ftp_quit(conn); /* ignore errors on the QUIT */

  if(ftpc->entrypath) {
    struct Curl_easy *data = conn->data;
    if(data->state.most_recent_ftp_entrypath == ftpc->entrypath) {
      data->state.most_recent_ftp_entrypath = NULL;
    }
    free(ftpc->entrypath);
    ftpc->entrypath = NULL;
  }

  freedirs(ftpc);
  free(ftpc->prevpath);
  ftpc->prevpath = NULL;
  free(ftpc->server_os);
  ftpc->server_os = NULL;

  Curl_pp_disconnect(pp);

#ifdef HAVE_GSSAPI
  Curl_sec_end(conn);
#endif

  return CURLE_OK;
}