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
struct inf {int /*<<< orphan*/  task; } ;

/* Variables and functions */
 struct inf* cur_inf () ; 
 int /*<<< orphan*/  error (char*) ; 

__attribute__((used)) static struct inf *
active_inf (void)
{
  struct inf *inf = cur_inf ();
  if (!inf->task)
    error ("No current process.");
  return inf;
}