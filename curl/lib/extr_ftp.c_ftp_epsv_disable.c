#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  count1; int /*<<< orphan*/  pp; } ;
struct TYPE_9__ {TYPE_2__ ftpc; } ;
struct TYPE_10__ {void* ftp_use_epsv; scalar_t__ socksproxy; scalar_t__ tunnel_proxy; scalar_t__ ipv6; } ;
struct connectdata {TYPE_3__ proto; TYPE_5__* data; TYPE_4__ bits; } ;
struct TYPE_7__ {void* errorbuf; } ;
struct TYPE_11__ {TYPE_1__ state; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLE_WEIRD_SERVER_REPLY ; 
 void* FALSE ; 
 int /*<<< orphan*/  FTP_PASV ; 
 int /*<<< orphan*/  PPSENDF (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  failf (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  infof (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode ftp_epsv_disable(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;

  if(conn->bits.ipv6 && !(conn->bits.tunnel_proxy || conn->bits.socksproxy)) {
    /* We can't disable EPSV when doing IPv6, so this is instead a fail */
    failf(conn->data, "Failed EPSV attempt, exiting\n");
    return CURLE_WEIRD_SERVER_REPLY;
  }

  infof(conn->data, "Failed EPSV attempt. Disabling EPSV\n");
  /* disable it for next transfer */
  conn->bits.ftp_use_epsv = FALSE;
  conn->data->state.errorbuf = FALSE; /* allow error message to get
                                         rewritten */
  PPSENDF(&conn->proto.ftpc.pp, "%s", "PASV");
  conn->proto.ftpc.count1++;
  /* remain in/go to the FTP_PASV state */
  state(conn, FTP_PASV);
  return result;
}