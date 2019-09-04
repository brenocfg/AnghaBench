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
struct ftp_conn {char transfertype; int /*<<< orphan*/  pp; } ;
struct TYPE_2__ {struct ftp_conn ftpc; } ;
struct connectdata {TYPE_1__ proto; } ;
typedef  int /*<<< orphan*/  ftpstate ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  PPSENDF (int /*<<< orphan*/ *,char*,char) ; 
 int /*<<< orphan*/  ftp_state_type_resp (struct connectdata*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode ftp_nb_type(struct connectdata *conn,
                            bool ascii, ftpstate newstate)
{
  struct ftp_conn *ftpc = &conn->proto.ftpc;
  CURLcode result;
  char want = (char)(ascii?'A':'I');

  if(ftpc->transfertype == want) {
    state(conn, newstate);
    return ftp_state_type_resp(conn, 200, newstate);
  }

  PPSENDF(&ftpc->pp, "TYPE %c", want);
  state(conn, newstate);

  /* keep track of our current transfer type */
  ftpc->transfertype = want;
  return CURLE_OK;
}