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
typedef  enum mips_loadgp_style { ____Placeholder_mips_loadgp_style } mips_loadgp_style ;
struct TYPE_4__ {TYPE_1__* machine; } ;
struct TYPE_3__ {scalar_t__ global_pointer; } ;

/* Variables and functions */
 int LOADGP_ABSOLUTE ; 
 int LOADGP_NEWABI ; 
 int LOADGP_NONE ; 
 int LOADGP_OLDABI ; 
 int /*<<< orphan*/  TARGET_ABICALLS ; 
 scalar_t__ TARGET_ABSOLUTE_ABICALLS ; 
 scalar_t__ TARGET_NEWABI ; 
 TYPE_2__* cfun ; 

enum mips_loadgp_style
mips_current_loadgp_style (void)
{
  if (!TARGET_ABICALLS || cfun->machine->global_pointer == 0)
    return LOADGP_NONE;

  if (TARGET_ABSOLUTE_ABICALLS)
    return LOADGP_ABSOLUTE;

  return TARGET_NEWABI ? LOADGP_NEWABI : LOADGP_OLDABI;
}