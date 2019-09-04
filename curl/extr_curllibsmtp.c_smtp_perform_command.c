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
struct TYPE_7__ {int /*<<< orphan*/  pp; } ;
struct TYPE_8__ {TYPE_3__ smtpc; } ;
struct connectdata {TYPE_4__ proto; struct Curl_easy* data; } ;
struct SMTP {char* custom; TYPE_2__* rcpt; } ;
struct TYPE_5__ {struct SMTP* protop; } ;
struct Curl_easy {TYPE_1__ req; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  Curl_pp_sendf (int /*<<< orphan*/ *,char*,char*,...) ; 
 int /*<<< orphan*/  SMTP_COMMAND ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode smtp_perform_command(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct SMTP *smtp = data->req.protop;

  /* Send the command */
  if(smtp->rcpt)
    result = Curl_pp_sendf(&conn->proto.smtpc.pp, "%s %s",
                           smtp->custom && smtp->custom[0] != '\0' ?
                           smtp->custom : "VRFY",
                           smtp->rcpt->data);
  else
    result = Curl_pp_sendf(&conn->proto.smtpc.pp, "%s",
                           smtp->custom && smtp->custom[0] != '\0' ?
                           smtp->custom : "HELP");

  if(!result)
    state(conn, SMTP_COMMAND);

  return result;
}