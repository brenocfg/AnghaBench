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
struct pop3_conn {scalar_t__ state; } ;
struct TYPE_2__ {struct pop3_conn pop3c; } ;
struct connectdata {TYPE_1__ proto; } ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ POP3_CAPA ; 
 int TRUE ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 

__attribute__((used)) static bool pop3_endofresp(struct connectdata *conn, char *line, size_t len,
                           int *resp)
{
  struct pop3_conn *pop3c = &conn->proto.pop3c;

  /* Do we have an error response? */
  if(len >= 4 && !memcmp("-ERR", line, 4)) {
    *resp = '-';

    return TRUE;
  }

  /* Are we processing CAPA command responses? */
  if(pop3c->state == POP3_CAPA) {
    /* Do we have the terminating line? */
    if(len >= 1 && line[0] == '.')
      /* Treat the response as a success */
      *resp = '+';
    else
      /* Treat the response as an untagged continuation */
      *resp = '*';

    return TRUE;
  }

  /* Do we have a success response? */
  if(len >= 3 && !memcmp("+OK", line, 3)) {
    *resp = '+';

    return TRUE;
  }

  /* Do we have a continuation response? */
  if(len >= 1 && line[0] == '+') {
    *resp = '*';

    return TRUE;
  }

  return FALSE; /* Nothing for us */
}