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
struct prunedead {struct connectdata* extracted; int /*<<< orphan*/  data; } ;
struct connectdata {int dummy; } ;

/* Variables and functions */
 scalar_t__ extract_if_dead (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int call_extract_if_dead(struct connectdata *conn, void *param)
{
  struct prunedead *p = (struct prunedead *)param;
  if(extract_if_dead(conn, p->data)) {
    /* stop the iteration here, pass back the connection that was extracted */
    p->extracted = conn;
    return 1;
  }
  return 0; /* continue iteration */
}