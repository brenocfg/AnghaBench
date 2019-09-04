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
struct TYPE_3__ {int /*<<< orphan*/  pp; } ;
struct TYPE_4__ {TYPE_1__ ftpc; } ;
struct connectdata {TYPE_2__ proto; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  FTP_PWD ; 
 int /*<<< orphan*/  PPSENDF (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode ftp_state_pwd(struct connectdata *conn)
{
  CURLcode result;

  /* send PWD to discover our entry point */
  PPSENDF(&conn->proto.ftpc.pp, "%s", "PWD");
  state(conn, FTP_PWD);

  return CURLE_OK;
}