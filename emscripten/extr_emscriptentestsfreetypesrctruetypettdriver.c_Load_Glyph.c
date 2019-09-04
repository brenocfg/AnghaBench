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
struct TYPE_6__ {scalar_t__ num_glyphs; } ;
struct TYPE_5__ {TYPE_2__* face; } ;
typedef  int /*<<< orphan*/  TT_Size ;
typedef  int /*<<< orphan*/  TT_GlyphSlot ;
typedef  scalar_t__ FT_UInt ;
typedef  int /*<<< orphan*/  FT_Size ;
typedef  int FT_Int32 ;
typedef  TYPE_1__* FT_GlyphSlot ;
typedef  TYPE_2__* FT_Face ;
typedef  int /*<<< orphan*/  FT_Error ;

/* Variables and functions */
 scalar_t__ FT_IS_TRICKY (TYPE_2__*) ; 
 int FT_LOAD_NO_AUTOHINT ; 
 int FT_LOAD_NO_BITMAP ; 
 int FT_LOAD_NO_HINTING ; 
 int FT_LOAD_NO_RECURSE ; 
 int FT_LOAD_NO_SCALE ; 
 int /*<<< orphan*/  TT_Err_Invalid_Argument ; 
 int /*<<< orphan*/  TT_Err_Invalid_Size_Handle ; 
 int /*<<< orphan*/  TT_Err_Invalid_Slot_Handle ; 
 int /*<<< orphan*/  TT_Load_Glyph (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static FT_Error
  Load_Glyph( FT_GlyphSlot  ttslot,         /* TT_GlyphSlot */
              FT_Size       ttsize,         /* TT_Size      */
              FT_UInt       glyph_index,
              FT_Int32      load_flags )
  {
    TT_GlyphSlot  slot = (TT_GlyphSlot)ttslot;
    TT_Size       size = (TT_Size)ttsize;
    FT_Face       face = ttslot->face;
    FT_Error      error;


    if ( !slot )
      return TT_Err_Invalid_Slot_Handle;

    if ( !size )
      return TT_Err_Invalid_Size_Handle;

    if ( !face )
      return TT_Err_Invalid_Argument;

#ifdef FT_CONFIG_OPTION_INCREMENTAL
    if ( glyph_index >= (FT_UInt)face->num_glyphs &&
         !face->internal->incremental_interface   )
#else
    if ( glyph_index >= (FT_UInt)face->num_glyphs )
#endif
      return TT_Err_Invalid_Argument;

    if ( load_flags & FT_LOAD_NO_HINTING )
    {
      /* both FT_LOAD_NO_HINTING and FT_LOAD_NO_AUTOHINT   */
      /* are necessary to disable hinting for tricky fonts */          

      if ( FT_IS_TRICKY( face ) )
        load_flags &= ~FT_LOAD_NO_HINTING;

      if ( load_flags & FT_LOAD_NO_AUTOHINT )
        load_flags |= FT_LOAD_NO_HINTING;
    }

    if ( load_flags & ( FT_LOAD_NO_RECURSE | FT_LOAD_NO_SCALE ) )
    {
      load_flags |= FT_LOAD_NO_BITMAP | FT_LOAD_NO_SCALE;

      if ( !FT_IS_TRICKY( face ) )
        load_flags |= FT_LOAD_NO_HINTING;
    }

    /* now load the glyph outline if necessary */
    error = TT_Load_Glyph( size, slot, glyph_index, load_flags );

    /* force drop-out mode to 2 - irrelevant now */
    /* slot->outline.dropout_mode = 2; */

    return error;
  }