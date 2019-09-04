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
struct ftp_conn {scalar_t__ file; int /*<<< orphan*/  pp; } ;
struct TYPE_3__ {struct ftp_conn ftpc; } ;
struct connectdata {TYPE_1__ proto; struct Curl_easy* data; } ;
struct TYPE_4__ {scalar_t__ timecondition; scalar_t__ get_filetime; } ;
struct Curl_easy {TYPE_2__ set; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  FTP_MDTM ; 
 int /*<<< orphan*/  PPSENDF (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  ftp_state_type (struct connectdata*) ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode ftp_state_mdtm(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct ftp_conn *ftpc = &conn->proto.ftpc;

  /* Requested time of file or time-depended transfer? */
  if((data->set.get_filetime || data->set.timecondition) && ftpc->file) {

    /* we have requested to get the modified-time of the file, this is a white
       spot as the MDTM is not mentioned in RFC959 */
    PPSENDF(&ftpc->pp, "MDTM %s", ftpc->file);

    state(conn, FTP_MDTM);
  }
  else
    result = ftp_state_type(conn);

  return result;
}