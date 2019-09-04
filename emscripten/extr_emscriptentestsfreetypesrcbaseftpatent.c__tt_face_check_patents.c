#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ num_glyphs; int /*<<< orphan*/  stream; } ;
struct TYPE_8__ {scalar_t__ (* get_location ) (TYPE_2__*,scalar_t__,scalar_t__*) ;} ;
typedef  scalar_t__ FT_ULong ;
typedef  scalar_t__ FT_UInt ;
typedef  int /*<<< orphan*/  FT_Stream ;
typedef  TYPE_1__* FT_Service_TTGlyf ;
typedef  int FT_Int ;
typedef  TYPE_2__* FT_Face ;
typedef  int /*<<< orphan*/  FT_Error ;
typedef  int FT_Bool ;

/* Variables and functions */
 int /*<<< orphan*/  FT_FACE_FIND_SERVICE (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ FT_READ_SHORT (int) ; 
 scalar_t__ FT_READ_USHORT (scalar_t__) ; 
 scalar_t__ FT_STREAM_SEEK (scalar_t__) ; 
 scalar_t__ FT_STREAM_SKIP (scalar_t__) ; 
 int /*<<< orphan*/  TTAG_fpgm ; 
 int /*<<< orphan*/  TTAG_prep ; 
 int /*<<< orphan*/  TT_GLYF ; 
 int _tt_check_patents_in_range (int /*<<< orphan*/ ,scalar_t__) ; 
 int _tt_check_patents_in_table (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_2__*,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static FT_Bool
  _tt_face_check_patents( FT_Face  face )
  {
    FT_Stream  stream = face->stream;
    FT_UInt    gindex;
    FT_Error   error;
    FT_Bool    result;

    FT_Service_TTGlyf  service;


    result = _tt_check_patents_in_table( face, TTAG_fpgm );
    if ( result )
      goto Exit;

    result = _tt_check_patents_in_table( face, TTAG_prep );
    if ( result )
      goto Exit;

    FT_FACE_FIND_SERVICE( face, service, TT_GLYF );
    if ( service == NULL )
      goto Exit;

    for ( gindex = 0; gindex < (FT_UInt)face->num_glyphs; gindex++ )
    {
      FT_ULong  offset, num_ins, size;
      FT_Int    num_contours;


      offset = service->get_location( face, gindex, &size );
      if ( size == 0 )
        continue;

      if ( FT_STREAM_SEEK( offset )      ||
           FT_READ_SHORT( num_contours ) )
        continue;

      if ( num_contours >= 0 )  /* simple glyph */
      {
        if ( FT_STREAM_SKIP( 8 + num_contours * 2 ) )
          continue;
      }
      else  /* compound glyph */
      {
        FT_Bool  has_instr = 0;


        if ( FT_STREAM_SKIP( 8 ) )
          continue;

        /* now read each component */
        for (;;)
        {
          FT_UInt  flags, toskip;


          if( FT_READ_USHORT( flags ) )
            break;

          toskip = 2 + 1 + 1;

          if ( ( flags & ( 1 << 0 ) ) != 0 )       /* ARGS_ARE_WORDS */
            toskip += 2;

          if ( ( flags & ( 1 << 3 ) ) != 0 )       /* WE_HAVE_A_SCALE */
            toskip += 2;
          else if ( ( flags & ( 1 << 6 ) ) != 0 )  /* WE_HAVE_X_Y_SCALE */
            toskip += 4;
          else if ( ( flags & ( 1 << 7 ) ) != 0 )  /* WE_HAVE_A_2x2 */
            toskip += 8;

          if ( ( flags & ( 1 << 8 ) ) != 0 )       /* WE_HAVE_INSTRUCTIONS */
            has_instr = 1;

          if ( FT_STREAM_SKIP( toskip ) )
            goto NextGlyph;

          if ( ( flags & ( 1 << 5 ) ) == 0 )       /* MORE_COMPONENTS */
            break;
        }

        if ( !has_instr )
          goto NextGlyph;
      }

      if ( FT_READ_USHORT( num_ins ) )
        continue;

      result = _tt_check_patents_in_range( stream, num_ins );
      if ( result )
        goto Exit;

    NextGlyph:
      ;
    }

  Exit:
    return result;
  }