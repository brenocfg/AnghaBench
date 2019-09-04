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
struct TYPE_6__ {TYPE_2__ pop3c; } ;
struct TYPE_4__ {int /*<<< orphan*/  user_passwd; } ;
struct connectdata {char* user; TYPE_3__ proto; TYPE_1__ bits; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  Curl_pp_sendf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  POP3_STOP ; 
 int /*<<< orphan*/  POP3_USER ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode pop3_perform_user(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;

  /* Check we have a username and password to authenticate with and end the
     connect phase if we don't */
  if(!conn->bits.user_passwd) {
    state(conn, POP3_STOP);

    return result;
  }

  /* Send the USER command */
  result = Curl_pp_sendf(&conn->proto.pop3c.pp, "USER %s",
                         conn->user ? conn->user : "");
  if(!result)
    state(conn, POP3_USER);

  return result;
}