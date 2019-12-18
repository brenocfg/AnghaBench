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
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  PU_STATIC ; 
 int W_GetNumForName (char*) ; 
 int W_LumpLength (int) ; 
 int /*<<< orphan*/  W_ReadLump (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Z_Malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * colormaps ; 

void R_InitColormaps (void)
{
    int	lump, length;
    
    // Load in the light tables, 
    //  256 byte align tables.
    lump = W_GetNumForName("COLORMAP"); 
    length = W_LumpLength (lump) + 255; 
    colormaps = Z_Malloc (length, PU_STATIC, 0); 
    colormaps = (byte *)( ((int)colormaps + 255)&~0xff); 
    W_ReadLump (lump,colormaps); 
}