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
struct TYPE_2__ {int /*<<< orphan*/  (* doing ) (struct connectdata*,int*) ;} ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_OK ; 
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  stub1 (struct connectdata*,int*) ; 

__attribute__((used)) static CURLcode protocol_doing(struct connectdata *conn, bool *done)
{
  CURLcode result = CURLE_OK;

  if(conn && conn->handler->doing) {
    *done = FALSE;
    result = conn->handler->doing(conn, done);
  }
  else
    *done = TRUE;

  return result;
}