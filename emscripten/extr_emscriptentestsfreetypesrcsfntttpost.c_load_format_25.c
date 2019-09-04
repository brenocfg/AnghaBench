#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  memory; } ;
struct TYPE_12__ {scalar_t__* offsets; scalar_t__ num_glyphs; } ;
struct TYPE_10__ {TYPE_4__ format_25; } ;
struct TYPE_11__ {TYPE_2__ names; } ;
struct TYPE_9__ {int numGlyphs; } ;
struct TYPE_13__ {TYPE_3__ postscript_names; TYPE_1__ max_profile; } ;
typedef  TYPE_4__* TT_Post_25 ;
typedef  TYPE_5__* TT_Face ;
typedef  scalar_t__ FT_UShort ;
typedef  TYPE_6__* FT_Stream ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  scalar_t__ FT_Long ;
typedef  int FT_Int ;
typedef  int /*<<< orphan*/  FT_Error ;
typedef  scalar_t__ FT_Char ;

/* Variables and functions */
 int /*<<< orphan*/  FT_FREE (scalar_t__*) ; 
 scalar_t__ FT_NEW_ARRAY (scalar_t__*,int) ; 
 scalar_t__ FT_READ_USHORT (int) ; 
 scalar_t__ FT_STREAM_READ (scalar_t__*,int) ; 
 int /*<<< orphan*/  FT_UNUSED (scalar_t__) ; 
 int /*<<< orphan*/  SFNT_Err_Invalid_File_Format ; 
 int /*<<< orphan*/  SFNT_Err_Ok ; 

__attribute__((used)) static FT_Error
  load_format_25( TT_Face    face,
                  FT_Stream  stream,
                  FT_Long    post_limit )
  {
    FT_Memory  memory = stream->memory;
    FT_Error   error;

    FT_Int     num_glyphs;
    FT_Char*   offset_table = 0;

    FT_UNUSED( post_limit );


    /* UNDOCUMENTED!  This value appears only in the Apple TT specs. */
    if ( FT_READ_USHORT( num_glyphs ) )
      goto Exit;

    /* check the number of glyphs */
    if ( num_glyphs > face->max_profile.numGlyphs || num_glyphs > 258 )
    {
      error = SFNT_Err_Invalid_File_Format;
      goto Exit;
    }

    if ( FT_NEW_ARRAY( offset_table, num_glyphs )   ||
         FT_STREAM_READ( offset_table, num_glyphs ) )
      goto Fail;

    /* now check the offset table */
    {
      FT_Int  n;


      for ( n = 0; n < num_glyphs; n++ )
      {
        FT_Long  idx = (FT_Long)n + offset_table[n];


        if ( idx < 0 || idx > num_glyphs )
        {
          error = SFNT_Err_Invalid_File_Format;
          goto Fail;
        }
      }
    }

    /* OK, set table fields and exit successfully */
    {
      TT_Post_25  table = &face->postscript_names.names.format_25;


      table->num_glyphs = (FT_UShort)num_glyphs;
      table->offsets    = offset_table;
    }

    return SFNT_Err_Ok;

  Fail:
    FT_FREE( offset_table );

  Exit:
    return error;
  }