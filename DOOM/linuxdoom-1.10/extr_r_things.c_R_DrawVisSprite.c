#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int mobjflags; int startfrac; scalar_t__ x1; scalar_t__ x2; scalar_t__ xiscale; int /*<<< orphan*/  scale; int /*<<< orphan*/  texturemid; int /*<<< orphan*/  colormap; int /*<<< orphan*/  patch; } ;
typedef  TYPE_1__ vissprite_t ;
struct TYPE_6__ {int /*<<< orphan*/ * columnofs; int /*<<< orphan*/  width; } ;
typedef  TYPE_2__ patch_t ;
typedef  int fixed_t ;
typedef  int /*<<< orphan*/  column_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int FRACBITS ; 
 scalar_t__ FixedMul (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I_Error (char*) ; 
 int LONG (int /*<<< orphan*/ ) ; 
 int MF_TRANSLATION ; 
 int MF_TRANSSHIFT ; 
 int /*<<< orphan*/  PU_CACHE ; 
 int /*<<< orphan*/  R_DrawMaskedColumn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  R_DrawTranslatedColumn ; 
 int SHORT (int /*<<< orphan*/ ) ; 
 TYPE_2__* W_CacheLumpNum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int abs (scalar_t__) ; 
 int /*<<< orphan*/  basecolfunc ; 
 scalar_t__ centeryfrac ; 
 int /*<<< orphan*/  colfunc ; 
 int /*<<< orphan*/  dc_colormap ; 
 int dc_iscale ; 
 int /*<<< orphan*/  dc_texturemid ; 
 int dc_translation ; 
 scalar_t__ dc_x ; 
 int detailshift ; 
 int firstspritelump ; 
 int /*<<< orphan*/  fuzzcolfunc ; 
 scalar_t__ sprtopscreen ; 
 int /*<<< orphan*/  spryscale ; 
 int translationtables ; 

void
R_DrawVisSprite
( vissprite_t*		vis,
  int			x1,
  int			x2 )
{
    column_t*		column;
    int			texturecolumn;
    fixed_t		frac;
    patch_t*		patch;
	
	
    patch = W_CacheLumpNum (vis->patch+firstspritelump, PU_CACHE);

    dc_colormap = vis->colormap;
    
    if (!dc_colormap)
    {
	// NULL colormap = shadow draw
	colfunc = fuzzcolfunc;
    }
    else if (vis->mobjflags & MF_TRANSLATION)
    {
	colfunc = R_DrawTranslatedColumn;
	dc_translation = translationtables - 256 +
	    ( (vis->mobjflags & MF_TRANSLATION) >> (MF_TRANSSHIFT-8) );
    }
	
    dc_iscale = abs(vis->xiscale)>>detailshift;
    dc_texturemid = vis->texturemid;
    frac = vis->startfrac;
    spryscale = vis->scale;
    sprtopscreen = centeryfrac - FixedMul(dc_texturemid,spryscale);
	
    for (dc_x=vis->x1 ; dc_x<=vis->x2 ; dc_x++, frac += vis->xiscale)
    {
	texturecolumn = frac>>FRACBITS;
#ifdef RANGECHECK
	if (texturecolumn < 0 || texturecolumn >= SHORT(patch->width))
	    I_Error ("R_DrawSpriteRange: bad texturecolumn");
#endif
	column = (column_t *) ((byte *)patch +
			       LONG(patch->columnofs[texturecolumn]));
	R_DrawMaskedColumn (column);
    }

    colfunc = basecolfunc;
}