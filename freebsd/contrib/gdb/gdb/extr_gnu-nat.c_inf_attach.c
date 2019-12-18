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
struct inf {scalar_t__ pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  inf_debug (struct inf*,char*,int) ; 
 int /*<<< orphan*/  inf_detach (struct inf*) ; 
 int /*<<< orphan*/  inf_startup (struct inf*,int) ; 

void
inf_attach (struct inf *inf, int pid)
{
  inf_debug (inf, "attaching: %d", pid);

  if (inf->pid)
    inf_detach (inf);

  inf_startup (inf, pid);
}