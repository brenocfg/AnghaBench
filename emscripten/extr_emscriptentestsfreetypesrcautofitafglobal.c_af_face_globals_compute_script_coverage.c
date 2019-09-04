#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int* glyph_scripts; size_t glyph_count; TYPE_1__* face; } ;
struct TYPE_13__ {TYPE_2__* script_uni_ranges; } ;
struct TYPE_12__ {scalar_t__ first; size_t last; } ;
struct TYPE_11__ {int /*<<< orphan*/  charmap; } ;
typedef  size_t FT_ULong ;
typedef  size_t FT_UInt ;
typedef  size_t FT_Long ;
typedef  TYPE_1__* FT_Face ;
typedef  scalar_t__ FT_Error ;
typedef  int /*<<< orphan*/  FT_CharMap ;
typedef  int FT_Byte ;
typedef  TYPE_2__* AF_Script_UniRange ;
typedef  TYPE_3__* AF_ScriptClass ;
typedef  TYPE_4__* AF_FaceGlobals ;

/* Variables and functions */
 int AF_DIGIT ; 
 scalar_t__ AF_Err_Ok ; 
 TYPE_3__** AF_SCRIPT_CLASSES_GET ; 
 int AF_SCRIPT_LIST_DEFAULT ; 
 int AF_SCRIPT_LIST_NONE ; 
 int /*<<< orphan*/  FT_ENCODING_UNICODE ; 
 size_t FT_Get_Char_Index (TYPE_1__*,size_t) ; 
 size_t FT_Get_Next_Char (TYPE_1__*,size_t,size_t*) ; 
 int /*<<< orphan*/  FT_MEM_SET (int*,int,size_t) ; 
 scalar_t__ FT_Select_Charmap (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FT_Set_Charmap (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static FT_Error
  af_face_globals_compute_script_coverage( AF_FaceGlobals  globals )
  {
    FT_Error    error       = AF_Err_Ok;
    FT_Face     face        = globals->face;
    FT_CharMap  old_charmap = face->charmap;
    FT_Byte*    gscripts    = globals->glyph_scripts;
    FT_UInt     ss, i;


    /* the value 255 means `uncovered glyph' */
    FT_MEM_SET( globals->glyph_scripts,
                AF_SCRIPT_LIST_NONE,
                globals->glyph_count );

    error = FT_Select_Charmap( face, FT_ENCODING_UNICODE );
    if ( error )
    {
     /*
      *  Ignore this error; we simply use the default script.
      *  XXX: Shouldn't we rather disable hinting?
      */
      error = AF_Err_Ok;
      goto Exit;
    }

    /* scan each script in a Unicode charmap */
    for ( ss = 0; AF_SCRIPT_CLASSES_GET[ss]; ss++ )
    {
      AF_ScriptClass      clazz = AF_SCRIPT_CLASSES_GET[ss];
      AF_Script_UniRange  range;


      if ( clazz->script_uni_ranges == NULL )
        continue;

      /*
       *  Scan all unicode points in the range and set the corresponding
       *  glyph script index.
       */
      for ( range = clazz->script_uni_ranges; range->first != 0; range++ )
      {
        FT_ULong  charcode = range->first;
        FT_UInt   gindex;


        gindex = FT_Get_Char_Index( face, charcode );

        if ( gindex != 0                             &&
             gindex < (FT_ULong)globals->glyph_count &&
             gscripts[gindex] == AF_SCRIPT_LIST_NONE )
        {
          gscripts[gindex] = (FT_Byte)ss;
        }

        for (;;)
        {
          charcode = FT_Get_Next_Char( face, charcode, &gindex );

          if ( gindex == 0 || charcode > range->last )
            break;

          if ( gindex < (FT_ULong)globals->glyph_count &&
               gscripts[gindex] == AF_SCRIPT_LIST_NONE )
          {
            gscripts[gindex] = (FT_Byte)ss;
          }
        }
      }
    }

    /* mark ASCII digits */
    for ( i = 0x30; i <= 0x39; i++ )
    {
      FT_UInt  gindex = FT_Get_Char_Index( face, i );


      if ( gindex != 0 && gindex < (FT_ULong)globals->glyph_count )
        gscripts[gindex] |= AF_DIGIT;
    }

  Exit:
    /*
     *  By default, all uncovered glyphs are set to the latin script.
     *  XXX: Shouldn't we disable hinting or do something similar?
     */
    {
      FT_Long  nn;


      for ( nn = 0; nn < globals->glyph_count; nn++ )
      {
        if ( ( gscripts[nn] & ~AF_DIGIT ) == AF_SCRIPT_LIST_NONE )
        {
          gscripts[nn] &= ~AF_SCRIPT_LIST_NONE;
          gscripts[nn] |= AF_SCRIPT_LIST_DEFAULT;
        }
      }
    }

    FT_Set_Charmap( face, old_charmap );
    return error;
  }