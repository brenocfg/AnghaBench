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
typedef  int /*<<< orphan*/  player_t ;

/* Variables and functions */
 int /*<<< orphan*/  NetUpdate () ; 
 int /*<<< orphan*/  R_ClearClipSegs () ; 
 int /*<<< orphan*/  R_ClearDrawSegs () ; 
 int /*<<< orphan*/  R_ClearPlanes () ; 
 int /*<<< orphan*/  R_ClearSprites () ; 
 int /*<<< orphan*/  R_DrawMasked () ; 
 int /*<<< orphan*/  R_DrawPlanes () ; 
 int /*<<< orphan*/  R_RenderBSPNode (scalar_t__) ; 
 int /*<<< orphan*/  R_SetupFrame (int /*<<< orphan*/ *) ; 
 scalar_t__ numnodes ; 

void R_RenderPlayerView (player_t* player)
{	
    R_SetupFrame (player);

    // Clear buffers.
    R_ClearClipSegs ();
    R_ClearDrawSegs ();
    R_ClearPlanes ();
    R_ClearSprites ();
    
    // check for new console commands.
    NetUpdate ();

    // The head node is the last node output.
    R_RenderBSPNode (numnodes-1);
    
    // Check for new console commands.
    NetUpdate ();
    
    R_DrawPlanes ();
    
    // Check for new console commands.
    NetUpdate ();
    
    R_DrawMasked ();

    // Check for new console commands.
    NetUpdate ();				
}