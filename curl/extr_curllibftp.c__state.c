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
struct ftp_conn {int /*<<< orphan*/  state; } ;
struct TYPE_2__ {struct ftp_conn ftpc; } ;
struct connectdata {TYPE_1__ proto; } ;
typedef  int /*<<< orphan*/  ftpstate ;

/* Variables and functions */

__attribute__((used)) static void _state(struct connectdata *conn,
                   ftpstate newstate
#ifdef DEBUGBUILD
                   , int lineno
#endif
  )
{
  struct ftp_conn *ftpc = &conn->proto.ftpc;

#if defined(DEBUGBUILD)

#if defined(CURL_DISABLE_VERBOSE_STRINGS)
  (void) lineno;
#else
  if(ftpc->state != newstate)
    infof(conn->data, "FTP %p (line %d) state change from %s to %s\n",
          (void *)ftpc, lineno, ftp_state_names[ftpc->state],
          ftp_state_names[newstate]);
#endif
#endif

  ftpc->state = newstate;
}