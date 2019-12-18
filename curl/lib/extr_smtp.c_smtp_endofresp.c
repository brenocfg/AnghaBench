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
typedef  int /*<<< orphan*/  tmpline ;
struct smtp_conn {scalar_t__ state; } ;
struct TYPE_2__ {struct smtp_conn smtpc; } ;
struct connectdata {TYPE_1__ proto; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  ISDIGIT (char) ; 
 scalar_t__ SMTP_COMMAND ; 
 scalar_t__ SMTP_EHLO ; 
 int TRUE ; 
 int curlx_sltosi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool smtp_endofresp(struct connectdata *conn, char *line, size_t len,
                           int *resp)
{
  struct smtp_conn *smtpc = &conn->proto.smtpc;
  bool result = FALSE;

  /* Nothing for us */
  if(len < 4 || !ISDIGIT(line[0]) || !ISDIGIT(line[1]) || !ISDIGIT(line[2]))
    return FALSE;

  /* Do we have a command response? This should be the response code followed
     by a space and optionally some text as per RFC-5321 and as outlined in
     Section 4. Examples of RFC-4954 but some e-mail servers ignore this and
     only send the response code instead as per Section 4.2. */
  if(line[3] == ' ' || len == 5) {
    char tmpline[6];

    result = TRUE;
    memset(tmpline, '\0', sizeof(tmpline));
    memcpy(tmpline, line, (len == 5 ? 5 : 3));
    *resp = curlx_sltosi(strtol(tmpline, NULL, 10));

    /* Make sure real server never sends internal value */
    if(*resp == 1)
      *resp = 0;
  }
  /* Do we have a multiline (continuation) response? */
  else if(line[3] == '-' &&
          (smtpc->state == SMTP_EHLO || smtpc->state == SMTP_COMMAND)) {
    result = TRUE;
    *resp = 1;  /* Internal response code */
  }

  return result;
}