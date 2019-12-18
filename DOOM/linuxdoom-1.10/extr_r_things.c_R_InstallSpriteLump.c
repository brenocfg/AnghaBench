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
typedef  void* byte ;
typedef  scalar_t__ boolean ;
struct TYPE_2__ {int rotate; int* lump; void** flip; } ;

/* Variables and functions */
 int /*<<< orphan*/  I_Error (char*,int,...) ; 
 int firstspritelump ; 
 int maxframe ; 
 int /*<<< orphan*/  spritename ; 
 TYPE_1__* sprtemp ; 

void
R_InstallSpriteLump
( int		lump,
  unsigned	frame,
  unsigned	rotation,
  boolean	flipped )
{
    int		r;
	
    if (frame >= 29 || rotation > 8)
	I_Error("R_InstallSpriteLump: "
		"Bad frame characters in lump %i", lump);
	
    if ((int)frame > maxframe)
	maxframe = frame;
		
    if (rotation == 0)
    {
	// the lump should be used for all rotations
	if (sprtemp[frame].rotate == false)
	    I_Error ("R_InitSprites: Sprite %s frame %c has "
		     "multip rot=0 lump", spritename, 'A'+frame);

	if (sprtemp[frame].rotate == true)
	    I_Error ("R_InitSprites: Sprite %s frame %c has rotations "
		     "and a rot=0 lump", spritename, 'A'+frame);
			
	sprtemp[frame].rotate = false;
	for (r=0 ; r<8 ; r++)
	{
	    sprtemp[frame].lump[r] = lump - firstspritelump;
	    sprtemp[frame].flip[r] = (byte)flipped;
	}
	return;
    }
	
    // the lump is only used for one rotation
    if (sprtemp[frame].rotate == false)
	I_Error ("R_InitSprites: Sprite %s frame %c has rotations "
		 "and a rot=0 lump", spritename, 'A'+frame);
		
    sprtemp[frame].rotate = true;

    // make 0 based
    rotation--;		
    if (sprtemp[frame].lump[rotation] != -1)
	I_Error ("R_InitSprites: Sprite %s : %c : %c "
		 "has two lumps mapped to it",
		 spritename, 'A'+frame, '1'+rotation);
		
    sprtemp[frame].lump[rotation] = lump - firstspritelump;
    sprtemp[frame].flip[rotation] = (byte)flipped;
}