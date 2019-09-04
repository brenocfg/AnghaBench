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
typedef  int /*<<< orphan*/  SFG_Font ;

/* Variables and functions */
 void* GLUT_BITMAP_8_BY_13 ; 
 void* GLUT_BITMAP_9_BY_15 ; 
 void* GLUT_BITMAP_HELVETICA_10 ; 
 void* GLUT_BITMAP_HELVETICA_12 ; 
 void* GLUT_BITMAP_HELVETICA_18 ; 
 void* GLUT_BITMAP_TIMES_ROMAN_10 ; 
 void* GLUT_BITMAP_TIMES_ROMAN_24 ; 
 int /*<<< orphan*/  fgFontFixed8x13 ; 
 int /*<<< orphan*/  fgFontFixed9x15 ; 
 int /*<<< orphan*/  fgFontHelvetica10 ; 
 int /*<<< orphan*/  fgFontHelvetica12 ; 
 int /*<<< orphan*/  fgFontHelvetica18 ; 
 int /*<<< orphan*/  fgFontTimesRoman10 ; 
 int /*<<< orphan*/  fgFontTimesRoman24 ; 
 int /*<<< orphan*/  fgWarning (char*,void*) ; 

__attribute__((used)) static SFG_Font* fghFontByID( void* font )
{
    if( font == GLUT_BITMAP_8_BY_13        )
        return &fgFontFixed8x13;
    if( font == GLUT_BITMAP_9_BY_15        )
        return &fgFontFixed9x15;
    if( font == GLUT_BITMAP_HELVETICA_10   )
        return &fgFontHelvetica10;
    if( font == GLUT_BITMAP_HELVETICA_12   )
        return &fgFontHelvetica12;
    if( font == GLUT_BITMAP_HELVETICA_18   )
        return &fgFontHelvetica18;
    if( font == GLUT_BITMAP_TIMES_ROMAN_10 )
        return &fgFontTimesRoman10;
    if( font == GLUT_BITMAP_TIMES_ROMAN_24 )
        return &fgFontTimesRoman24;

    fgWarning( "font 0x%08x not found", font );
    return 0;
}