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
struct imap_conn {int /*<<< orphan*/  pp; } ;
struct TYPE_2__ {struct imap_conn imapc; } ;
struct connectdata {TYPE_1__ proto; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_pp_sendf (int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static CURLcode imap_continue_authenticate(struct connectdata *conn,
                                           const char *resp)
{
  struct imap_conn *imapc = &conn->proto.imapc;

  return Curl_pp_sendf(&imapc->pp, "%s", resp);
}