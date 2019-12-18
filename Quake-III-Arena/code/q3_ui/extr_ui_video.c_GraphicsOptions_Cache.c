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
 int /*<<< orphan*/  GRAPHICSOPTIONS_ACCEPT0 ; 
 int /*<<< orphan*/  GRAPHICSOPTIONS_ACCEPT1 ; 
 int /*<<< orphan*/  GRAPHICSOPTIONS_BACK0 ; 
 int /*<<< orphan*/  GRAPHICSOPTIONS_BACK1 ; 
 int /*<<< orphan*/  GRAPHICSOPTIONS_FRAMEL ; 
 int /*<<< orphan*/  GRAPHICSOPTIONS_FRAMER ; 
 int /*<<< orphan*/  trap_R_RegisterShaderNoMip (int /*<<< orphan*/ ) ; 

void GraphicsOptions_Cache( void ) {
	trap_R_RegisterShaderNoMip( GRAPHICSOPTIONS_FRAMEL );
	trap_R_RegisterShaderNoMip( GRAPHICSOPTIONS_FRAMER );
	trap_R_RegisterShaderNoMip( GRAPHICSOPTIONS_BACK0 );
	trap_R_RegisterShaderNoMip( GRAPHICSOPTIONS_BACK1 );
	trap_R_RegisterShaderNoMip( GRAPHICSOPTIONS_ACCEPT0 );
	trap_R_RegisterShaderNoMip( GRAPHICSOPTIONS_ACCEPT1 );
}