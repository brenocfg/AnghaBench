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
struct TYPE_5__ {int /*<<< orphan*/  pp; } ;
struct TYPE_6__ {TYPE_2__ ftpc; } ;
struct connectdata {TYPE_3__ proto; TYPE_1__* ssl; } ;
struct TYPE_4__ {scalar_t__ use; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 size_t FIRSTSOCKET ; 
 int /*<<< orphan*/  FTP_PBSZ ; 
 int /*<<< orphan*/  PPSENDF (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftp_state_pwd (struct connectdata*) ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode ftp_state_loggedin(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;

  if(conn->ssl[FIRSTSOCKET].use) {
    /* PBSZ = PROTECTION BUFFER SIZE.

    The 'draft-murray-auth-ftp-ssl' (draft 12, page 7) says:

    Specifically, the PROT command MUST be preceded by a PBSZ
    command and a PBSZ command MUST be preceded by a successful
    security data exchange (the TLS negotiation in this case)

    ... (and on page 8):

    Thus the PBSZ command must still be issued, but must have a
    parameter of '0' to indicate that no buffering is taking place
    and the data connection should not be encapsulated.
    */
    PPSENDF(&conn->proto.ftpc.pp, "PBSZ %d", 0);
    state(conn, FTP_PBSZ);
  }
  else {
    result = ftp_state_pwd(conn);
  }
  return result;
}