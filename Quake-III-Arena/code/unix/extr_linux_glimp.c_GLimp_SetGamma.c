#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {float red; float green; float blue; } ;
typedef  TYPE_1__ XF86VidModeGamma ;
struct TYPE_7__ {float value; } ;
struct TYPE_6__ {int /*<<< orphan*/  deviceSupportsGamma; } ;

/* Variables and functions */
 TYPE_4__* Cvar_Get (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XF86VidModeSetGamma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpy ; 
 TYPE_2__ glConfig ; 
 int /*<<< orphan*/  scrnum ; 

void GLimp_SetGamma( unsigned char red[256], unsigned char green[256], unsigned char blue[256] )
{
  // NOTE TTimo we get the gamma value from cvar, because we can't work with the s_gammatable
  //   the API wasn't changed to avoid breaking other OSes
  float g = Cvar_Get("r_gamma", "1.0", 0)->value;
  XF86VidModeGamma gamma;
  assert(glConfig.deviceSupportsGamma);
  gamma.red = g;
  gamma.green = g;
  gamma.blue = g;
  XF86VidModeSetGamma(dpy, scrnum, &gamma);
}