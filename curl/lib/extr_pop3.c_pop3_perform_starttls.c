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
struct TYPE_4__ {TYPE_1__ pop3c; } ;
struct connectdata {TYPE_2__ proto; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  Curl_pp_sendf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  POP3_STARTTLS ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode pop3_perform_starttls(struct connectdata *conn)
{
  /* Send the STLS command */
  CURLcode result = Curl_pp_sendf(&conn->proto.pop3c.pp, "%s", "STLS");

  if(!result)
    state(conn, POP3_STARTTLS);

  return result;
}