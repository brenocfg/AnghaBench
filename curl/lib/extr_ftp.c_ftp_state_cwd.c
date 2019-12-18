#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ftp_conn {char** dirs; int count3; char* entrypath; int cwdcount; int /*<<< orphan*/  pp; scalar_t__ dirdepth; scalar_t__ count2; scalar_t__ cwddone; } ;
struct TYPE_8__ {struct ftp_conn ftpc; } ;
struct TYPE_7__ {scalar_t__ reuse; } ;
struct connectdata {TYPE_4__ proto; TYPE_3__ bits; TYPE_2__* data; } ;
struct TYPE_5__ {scalar_t__ ftp_filemethod; int ftp_create_missing_dirs; } ;
struct TYPE_6__ {TYPE_1__ set; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  DEBUGASSERT (int) ; 
 scalar_t__ FTPFILE_NOCWD ; 
 int /*<<< orphan*/  FTP_CWD ; 
 int /*<<< orphan*/  PPSENDF (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  ftp_state_mdtm (struct connectdata*) ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode ftp_state_cwd(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct ftp_conn *ftpc = &conn->proto.ftpc;

  if(ftpc->cwddone)
    /* already done and fine */
    result = ftp_state_mdtm(conn);
  else {
    /* FTPFILE_NOCWD with full path: expect ftpc->cwddone! */
    DEBUGASSERT((conn->data->set.ftp_filemethod != FTPFILE_NOCWD) ||
                !(ftpc->dirdepth && ftpc->dirs[0][0] == '/'));

    ftpc->count2 = 0; /* count2 counts failed CWDs */

    /* count3 is set to allow a MKD to fail once. In the case when first CWD
       fails and then MKD fails (due to another session raced it to create the
       dir) this then allows for a second try to CWD to it */
    ftpc->count3 = (conn->data->set.ftp_create_missing_dirs == 2)?1:0;

    if(conn->bits.reuse && ftpc->entrypath &&
       /* no need to go to entrypath when we have an absolute path */
       !(ftpc->dirdepth && ftpc->dirs[0][0] == '/')) {
      /* This is a re-used connection. Since we change directory to where the
         transfer is taking place, we must first get back to the original dir
         where we ended up after login: */
      ftpc->cwdcount = 0; /* we count this as the first path, then we add one
                             for all upcoming ones in the ftp->dirs[] array */
      PPSENDF(&conn->proto.ftpc.pp, "CWD %s", ftpc->entrypath);
      state(conn, FTP_CWD);
    }
    else {
      if(ftpc->dirdepth) {
        ftpc->cwdcount = 1;
        /* issue the first CWD, the rest is sent when the CWD responses are
           received... */
        PPSENDF(&conn->proto.ftpc.pp, "CWD %s", ftpc->dirs[ftpc->cwdcount -1]);
        state(conn, FTP_CWD);
      }
      else {
        /* No CWD necessary */
        result = ftp_state_mdtm(conn);
      }
    }
  }
  return result;
}