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
struct pingpong {int dummy; } ;
struct ftp_conn {scalar_t__ state; struct pingpong pp; } ;
struct TYPE_2__ {struct ftp_conn ftpc; } ;
struct connectdata {TYPE_1__ proto; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ Curl_pp_statemach (struct pingpong*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FTP_STOP ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static CURLcode ftp_block_statemach(struct connectdata *conn)
{
  struct ftp_conn *ftpc = &conn->proto.ftpc;
  struct pingpong *pp = &ftpc->pp;
  CURLcode result = CURLE_OK;

  while(ftpc->state != FTP_STOP) {
    result = Curl_pp_statemach(pp, TRUE, TRUE /* disconnecting */);
    if(result)
      break;
  }

  return result;
}