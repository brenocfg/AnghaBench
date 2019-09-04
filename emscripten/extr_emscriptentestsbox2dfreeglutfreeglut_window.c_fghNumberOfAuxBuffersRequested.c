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
struct TYPE_2__ {int DisplayMode; int AuxiliaryBufferNumber; } ;

/* Variables and functions */
 int GLUT_AUX1 ; 
 int GLUT_AUX2 ; 
 int GLUT_AUX3 ; 
 int GLUT_AUX4 ; 
 TYPE_1__ fgState ; 

__attribute__((used)) static int fghNumberOfAuxBuffersRequested( void )
{
  if ( fgState.DisplayMode & GLUT_AUX4 ) {
    return 4;
  }
  if ( fgState.DisplayMode & GLUT_AUX3 ) {
    return 3;
  }
  if ( fgState.DisplayMode & GLUT_AUX2 ) {
    return 2;
  }
  if ( fgState.DisplayMode & GLUT_AUX1 ) { /* NOTE: Same as GLUT_AUX! */
    return fgState.AuxiliaryBufferNumber;
  }
  return 0;
}