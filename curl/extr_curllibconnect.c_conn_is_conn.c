#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct connfind {int /*<<< orphan*/  found; struct connectdata* tofind; } ;
struct connectdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static int conn_is_conn(struct connectdata *conn, void *param)
{
  struct connfind *f = (struct connfind *)param;
  if(conn == f->tofind) {
    f->found = TRUE;
    return 1;
  }
  return 0;
}