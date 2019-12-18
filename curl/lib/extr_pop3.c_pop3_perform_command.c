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
struct TYPE_8__ {TYPE_3__ pop3c; } ;
struct connectdata {TYPE_4__ proto; struct Curl_easy* data; } ;
struct POP3 {char* id; char* custom; int /*<<< orphan*/  transfer; } ;
struct TYPE_6__ {scalar_t__ ftp_list_only; } ;
struct TYPE_5__ {struct POP3* protop; } ;
struct Curl_easy {TYPE_2__ set; TYPE_1__ req; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  Curl_pp_sendf (int /*<<< orphan*/ *,char*,char const*,...) ; 
 int /*<<< orphan*/  FTPTRANSFER_INFO ; 
 int /*<<< orphan*/  POP3_COMMAND ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode pop3_perform_command(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct POP3 *pop3 = data->req.protop;
  const char *command = NULL;

  /* Calculate the default command */
  if(pop3->id[0] == '\0' || conn->data->set.ftp_list_only) {
    command = "LIST";

    if(pop3->id[0] != '\0')
      /* Message specific LIST so skip the BODY transfer */
      pop3->transfer = FTPTRANSFER_INFO;
  }
  else
    command = "RETR";

  /* Send the command */
  if(pop3->id[0] != '\0')
    result = Curl_pp_sendf(&conn->proto.pop3c.pp, "%s %s",
                           (pop3->custom && pop3->custom[0] != '\0' ?
                            pop3->custom : command), pop3->id);
  else
    result = Curl_pp_sendf(&conn->proto.pop3c.pp, "%s",
                           (pop3->custom && pop3->custom[0] != '\0' ?
                            pop3->custom : command));

  if(!result)
    state(conn, POP3_COMMAND);

  return result;
}