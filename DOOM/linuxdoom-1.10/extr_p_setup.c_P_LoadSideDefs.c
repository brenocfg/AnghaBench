#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t textureoffset; size_t rowoffset; int /*<<< orphan*/ * sector; void* midtexture; void* bottomtexture; void* toptexture; } ;
typedef  TYPE_1__ side_t ;
struct TYPE_7__ {int /*<<< orphan*/  sector; int /*<<< orphan*/  midtexture; int /*<<< orphan*/  bottomtexture; int /*<<< orphan*/  toptexture; int /*<<< orphan*/  rowoffset; int /*<<< orphan*/  textureoffset; } ;
typedef  TYPE_2__ mapsidedef_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 size_t FRACBITS ; 
 int /*<<< orphan*/  PU_LEVEL ; 
 int /*<<< orphan*/  PU_STATIC ; 
 void* R_TextureNumForName (int /*<<< orphan*/ ) ; 
 size_t SHORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * W_CacheLumpNum (int,int /*<<< orphan*/ ) ; 
 int W_LumpLength (int) ; 
 int /*<<< orphan*/  Z_Free (int /*<<< orphan*/ *) ; 
 TYPE_1__* Z_Malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int numsides ; 
 int /*<<< orphan*/ * sectors ; 
 TYPE_1__* sides ; 

void P_LoadSideDefs (int lump)
{
    byte*		data;
    int			i;
    mapsidedef_t*	msd;
    side_t*		sd;
	
    numsides = W_LumpLength (lump) / sizeof(mapsidedef_t);
    sides = Z_Malloc (numsides*sizeof(side_t),PU_LEVEL,0);	
    memset (sides, 0, numsides*sizeof(side_t));
    data = W_CacheLumpNum (lump,PU_STATIC);
	
    msd = (mapsidedef_t *)data;
    sd = sides;
    for (i=0 ; i<numsides ; i++, msd++, sd++)
    {
	sd->textureoffset = SHORT(msd->textureoffset)<<FRACBITS;
	sd->rowoffset = SHORT(msd->rowoffset)<<FRACBITS;
	sd->toptexture = R_TextureNumForName(msd->toptexture);
	sd->bottomtexture = R_TextureNumForName(msd->bottomtexture);
	sd->midtexture = R_TextureNumForName(msd->midtexture);
	sd->sector = &sectors[SHORT(msd->sector)];
    }
	
    Z_Free (data);
}