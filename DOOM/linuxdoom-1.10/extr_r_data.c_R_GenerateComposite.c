#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int patchcount; int width; int /*<<< orphan*/  height; TYPE_2__* patches; } ;
typedef  TYPE_1__ texture_t ;
struct TYPE_7__ {int originx; int /*<<< orphan*/  originy; int /*<<< orphan*/  patch; } ;
typedef  TYPE_2__ texpatch_t ;
struct TYPE_8__ {int /*<<< orphan*/ * columnofs; int /*<<< orphan*/  width; } ;
typedef  TYPE_3__ patch_t ;
typedef  int /*<<< orphan*/  column_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int LONG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PU_CACHE ; 
 int /*<<< orphan*/  PU_STATIC ; 
 int /*<<< orphan*/  R_DrawColumnInCache (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SHORT (int /*<<< orphan*/ ) ; 
 TYPE_3__* W_CacheLumpNum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_ChangeTag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Z_Malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 short** texturecolumnlump ; 
 unsigned short** texturecolumnofs ; 
 int /*<<< orphan*/ * texturecomposite ; 
 int /*<<< orphan*/ * texturecompositesize ; 
 TYPE_1__** textures ; 

void R_GenerateComposite (int texnum)
{
    byte*		block;
    texture_t*		texture;
    texpatch_t*		patch;	
    patch_t*		realpatch;
    int			x;
    int			x1;
    int			x2;
    int			i;
    column_t*		patchcol;
    short*		collump;
    unsigned short*	colofs;
	
    texture = textures[texnum];

    block = Z_Malloc (texturecompositesize[texnum],
		      PU_STATIC, 
		      &texturecomposite[texnum]);	

    collump = texturecolumnlump[texnum];
    colofs = texturecolumnofs[texnum];
    
    // Composite the columns together.
    patch = texture->patches;
		
    for (i=0 , patch = texture->patches;
	 i<texture->patchcount;
	 i++, patch++)
    {
	realpatch = W_CacheLumpNum (patch->patch, PU_CACHE);
	x1 = patch->originx;
	x2 = x1 + SHORT(realpatch->width);

	if (x1<0)
	    x = 0;
	else
	    x = x1;
	
	if (x2 > texture->width)
	    x2 = texture->width;

	for ( ; x<x2 ; x++)
	{
	    // Column does not have multiple patches?
	    if (collump[x] >= 0)
		continue;
	    
	    patchcol = (column_t *)((byte *)realpatch
				    + LONG(realpatch->columnofs[x-x1]));
	    R_DrawColumnInCache (patchcol,
				 block + colofs[x],
				 patch->originy,
				 texture->height);
	}
						
    }

    // Now that the texture has been built in column cache,
    //  it is purgable from zone memory.
    Z_ChangeTag (block, PU_CACHE);
}