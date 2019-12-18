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
struct fpreg {int /*<<< orphan*/  fpr_fpsr; int /*<<< orphan*/ * fpr; } ;

/* Variables and functions */
 int ARM_F0_REGNUM ; 
 int ARM_F7_REGNUM ; 
 int ARM_FPS_REGNUM ; 
 int /*<<< orphan*/  supply_register (int,char*) ; 

__attribute__((used)) static void
supply_fparegset (struct fpreg *fparegset)
{
  int regno;

  for (regno = ARM_F0_REGNUM; regno <= ARM_F7_REGNUM; regno++)
    supply_register
      (regno, (char *) &fparegset->fpr[regno - ARM_F0_REGNUM]);

  supply_register (ARM_FPS_REGNUM, (char *) &fparegset->fpr_fpsr);
}