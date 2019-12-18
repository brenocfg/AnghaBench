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
 int /*<<< orphan*/  R_InitData () ; 
 int /*<<< orphan*/  R_InitLightTables () ; 
 int /*<<< orphan*/  R_InitPlanes () ; 
 int /*<<< orphan*/  R_InitPointToAngle () ; 
 int /*<<< orphan*/  R_InitSkyMap () ; 
 int /*<<< orphan*/  R_InitTables () ; 
 int /*<<< orphan*/  R_InitTranslationTables () ; 
 int /*<<< orphan*/  R_SetViewSize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  detailLevel ; 
 scalar_t__ framecount ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  screenblocks ; 

void R_Init (void)
{
    R_InitData ();
    printf ("\nR_InitData");
    R_InitPointToAngle ();
    printf ("\nR_InitPointToAngle");
    R_InitTables ();
    // viewwidth / viewheight / detailLevel are set by the defaults
    printf ("\nR_InitTables");

    R_SetViewSize (screenblocks, detailLevel);
    R_InitPlanes ();
    printf ("\nR_InitPlanes");
    R_InitLightTables ();
    printf ("\nR_InitLightTables");
    R_InitSkyMap ();
    printf ("\nR_InitSkyMap");
    R_InitTranslationTables ();
    printf ("\nR_InitTranslationsTables");
	
    framecount = 0;
}