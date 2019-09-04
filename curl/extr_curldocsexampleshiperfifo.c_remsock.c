#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ev; } ;
typedef  TYPE_1__ SockInfo ;

/* Variables and functions */
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void remsock(SockInfo *f)
{
  if(f) {
    event_del(&f->ev);
    free(f);
  }
}