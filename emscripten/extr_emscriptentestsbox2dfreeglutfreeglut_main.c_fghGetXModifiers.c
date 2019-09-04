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

/* Variables and functions */
 int ControlMask ; 
 int GLUT_ACTIVE_ALT ; 
 int GLUT_ACTIVE_CTRL ; 
 int GLUT_ACTIVE_SHIFT ; 
 int LockMask ; 
 int Mod1Mask ; 
 int ShiftMask ; 

__attribute__((used)) static int fghGetXModifiers( int state )
{
    int ret = 0;

    if( state & ( ShiftMask | LockMask ) )
        ret |= GLUT_ACTIVE_SHIFT;
    if( state & ControlMask )
        ret |= GLUT_ACTIVE_CTRL;
    if( state & Mod1Mask )
        ret |= GLUT_ACTIVE_ALT;

    return ret;
}