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
struct pop3_conn {int /*<<< orphan*/  state; } ;
struct TYPE_2__ {struct pop3_conn pop3c; } ;
struct connectdata {TYPE_1__ proto; } ;
typedef  int /*<<< orphan*/  pop3state ;

/* Variables and functions */

__attribute__((used)) static void state(struct connectdata *conn, pop3state newstate)
{
  struct pop3_conn *pop3c = &conn->proto.pop3c;
#if defined(DEBUGBUILD) && !defined(CURL_DISABLE_VERBOSE_STRINGS)
  /* for debug purposes */
  static const char * const names[] = {
    "STOP",
    "SERVERGREET",
    "CAPA",
    "STARTTLS",
    "UPGRADETLS",
    "AUTH",
    "APOP",
    "USER",
    "PASS",
    "COMMAND",
    "QUIT",
    /* LAST */
  };

  if(pop3c->state != newstate)
    infof(conn->data, "POP3 %p state change from %s to %s\n",
          (void *)pop3c, names[pop3c->state], names[newstate]);
#endif

  pop3c->state = newstate;
}