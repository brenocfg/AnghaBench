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
typedef  int /*<<< orphan*/  SFG_StrokeFont ;

/* Variables and functions */
 void* GLUT_STROKE_MONO_ROMAN ; 
 void* GLUT_STROKE_ROMAN ; 
 int /*<<< orphan*/  fgStrokeMonoRoman ; 
 int /*<<< orphan*/  fgStrokeRoman ; 
 int /*<<< orphan*/  fgWarning (char*,void*) ; 

__attribute__((used)) static SFG_StrokeFont* fghStrokeByID( void* font )
{
    if( font == GLUT_STROKE_ROMAN      )
        return &fgStrokeRoman;
    if( font == GLUT_STROKE_MONO_ROMAN )
        return &fgStrokeMonoRoman;

    fgWarning( "stroke font 0x%08x not found", font );
    return 0;
}