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
struct TYPE_3__ {scalar_t__ ctl_valid; int /*<<< orphan*/  pp; } ;
struct TYPE_4__ {TYPE_1__ ftpc; } ;
struct connectdata {TYPE_2__ proto; int /*<<< orphan*/  data; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ Curl_pp_sendf (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FTP_QUIT ; 
 int /*<<< orphan*/  FTP_STOP ; 
 int /*<<< orphan*/  connclose (struct connectdata*,char*) ; 
 int /*<<< orphan*/  curl_easy_strerror (scalar_t__) ; 
 int /*<<< orphan*/  failf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ftp_block_statemach (struct connectdata*) ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode ftp_quit(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;

  if(conn->proto.ftpc.ctl_valid) {
    result = Curl_pp_sendf(&conn->proto.ftpc.pp, "%s", "QUIT");
    if(result) {
      failf(conn->data, "Failure sending QUIT command: %s",
            curl_easy_strerror(result));
      conn->proto.ftpc.ctl_valid = FALSE; /* mark control connection as bad */
      connclose(conn, "QUIT command failed"); /* mark for connection closure */
      state(conn, FTP_STOP);
      return result;
    }

    state(conn, FTP_QUIT);

    result = ftp_block_statemach(conn);
  }

  return result;
}