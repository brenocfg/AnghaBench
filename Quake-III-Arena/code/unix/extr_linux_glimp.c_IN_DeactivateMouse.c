#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ value; } ;
struct TYPE_5__ {int /*<<< orphan*/  value; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* Cvar_Set ) (char*,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dpy ; 
 TYPE_3__* in_dgamouse ; 
 TYPE_2__* in_nograb ; 
 scalar_t__ mouse_active ; 
 int /*<<< orphan*/  mouse_avail ; 
 scalar_t__ qfalse ; 
 TYPE_1__ ri ; 
 int /*<<< orphan*/  stub1 (char*,char*) ; 
 int /*<<< orphan*/  uninstall_grabs () ; 
 int /*<<< orphan*/  win ; 

void IN_DeactivateMouse( void ) 
{
  if (!mouse_avail || !dpy || !win)
    return;

  if (mouse_active)
  {
		if (!in_nograb->value)
      uninstall_grabs();
		else if (in_dgamouse->value) // force dga mouse to 0 if using nograb
			ri.Cvar_Set("in_dgamouse", "0");
    mouse_active = qfalse;
  }
}