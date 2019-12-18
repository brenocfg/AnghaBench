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
struct TYPE_2__ {scalar_t__ specialfs; scalar_t__ special; } ;

/* Variables and functions */
 TYPE_1__ Settings ; 
 int _bpp ; 
 scalar_t__ _efx ; 
 scalar_t__ _efxfs ; 
 scalar_t__ _fullscreen ; 
 int _opengl ; 
 int _openglip ; 
 int _stretchx ; 
 scalar_t__ _stretchy ; 
 int _xres ; 
 double _xscale ; 
 int _xscalefs ; 
 int _yres ; 
 int _yscale ; 
 int _yscalefs ; 

__attribute__((used)) static void SetDefaults(void)
{
 Settings.special=Settings.specialfs=0;
 _bpp=8;
 _xres=640;
 _yres=480;
 _fullscreen=0;
 _xscale=2.50;
 _yscale=2;
 _xscalefs=_yscalefs=2;
 _efx=_efxfs=0;
 //_fshack=_fshacksave=0;
#ifdef OPENGL
 _opengl=1;
 _stretchx=1; 
 _stretchy=0;
 _openglip=1;
#endif
}