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
struct TYPE_3__ {int close; } ;
struct connectdata {TYPE_1__ bits; int /*<<< orphan*/  data; TYPE_2__* handler; } ;
typedef  int bit ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int CONNCTRL_CONNECTION ; 
 int CONNCTRL_STREAM ; 
 int /*<<< orphan*/  DEBUGF (int /*<<< orphan*/ ) ; 
 int PROTOPT_STREAM ; 
 int /*<<< orphan*/  infof (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  reason ; 

void Curl_conncontrol(struct connectdata *conn,
                      int ctrl /* see defines in header */
#if defined(DEBUGBUILD) && !defined(CURL_DISABLE_VERBOSE_STRINGS)
                      , const char *reason
#endif
  )
{
  /* close if a connection, or a stream that isn't multiplexed */
  bool closeit = (ctrl == CONNCTRL_CONNECTION) ||
    ((ctrl == CONNCTRL_STREAM) && !(conn->handler->flags & PROTOPT_STREAM));
  if((ctrl == CONNCTRL_STREAM) &&
     (conn->handler->flags & PROTOPT_STREAM))
    DEBUGF(infof(conn->data, "Kill stream: %s\n", reason));
  else if((bit)closeit != conn->bits.close) {
    DEBUGF(infof(conn->data, "Marked for [%s]: %s\n",
                 closeit?"closure":"keep alive", reason));
    conn->bits.close = closeit; /* the only place in the source code that
                                   should assign this bit */
  }
}