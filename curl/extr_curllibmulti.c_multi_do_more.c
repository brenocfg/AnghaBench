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
struct connectdata {TYPE_1__* handler; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* do_more ) (struct connectdata*,int*) ;} ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  do_complete (struct connectdata*) ; 
 int /*<<< orphan*/  stub1 (struct connectdata*,int*) ; 

__attribute__((used)) static CURLcode multi_do_more(struct connectdata *conn, int *complete)
{
  CURLcode result = CURLE_OK;

  *complete = 0;

  if(conn->handler->do_more)
    result = conn->handler->do_more(conn, complete);

  if(!result && (*complete == 1))
    /* do_complete must be called after the protocol-specific DO function */
    do_complete(conn);

  return result;
}