#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int* glyph_styles; size_t glyph_count; TYPE_1__* module; TYPE_2__* face; } ;
struct TYPE_20__ {TYPE_4__* script_uni_nonbase_ranges; TYPE_4__* script_uni_ranges; } ;
struct TYPE_19__ {scalar_t__ first; size_t last; } ;
struct TYPE_18__ {size_t script; scalar_t__ coverage; size_t style; } ;
struct TYPE_17__ {int /*<<< orphan*/  charmap; } ;
struct TYPE_16__ {size_t default_script; int fallback_style; } ;
typedef  int FT_UShort ;
typedef  size_t FT_ULong ;
typedef  size_t FT_UInt ;
typedef  size_t FT_Long ;
typedef  TYPE_2__* FT_Face ;
typedef  scalar_t__ FT_Error ;
typedef  int /*<<< orphan*/  FT_CharMap ;
typedef  TYPE_3__* AF_StyleClass ;
typedef  TYPE_4__* AF_Script_UniRange ;
typedef  TYPE_5__* AF_ScriptClass ;
typedef  TYPE_6__* AF_FaceGlobals ;

/* Variables and functions */
 scalar_t__ AF_COVERAGE_DEFAULT ; 
 int AF_DIGIT ; 
 int AF_NONBASE ; 
 TYPE_5__** AF_SCRIPT_CLASSES_GET ; 
 TYPE_3__** AF_STYLE_CLASSES_GET ; 
 int AF_STYLE_MASK ; 
 int AF_STYLE_UNASSIGNED ; 
 int /*<<< orphan*/  FT_ENCODING_UNICODE ; 
 scalar_t__ FT_Err_Ok ; 
 size_t FT_Get_Char_Index (TYPE_2__*,size_t) ; 
 size_t FT_Get_Next_Char (TYPE_2__*,size_t,size_t*) ; 
 scalar_t__ FT_Select_Charmap (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FT_Set_Charmap (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FT_TRACE4 (char*) ; 
 int /*<<< orphan*/  af_shaper_get_coverage (TYPE_6__*,TYPE_3__*,int*,int) ; 
 int /*<<< orphan*/ * af_style_names ; 

__attribute__((used)) static FT_Error
  af_face_globals_compute_style_coverage( AF_FaceGlobals  globals )
  {
    FT_Error    error;
    FT_Face     face        = globals->face;
    FT_CharMap  old_charmap = face->charmap;
    FT_UShort*  gstyles     = globals->glyph_styles;
    FT_UInt     ss;
    FT_UInt     i;
    FT_UInt     dflt        = ~0U; /* a non-valid value */


    /* the value AF_STYLE_UNASSIGNED means `uncovered glyph' */
    for ( i = 0; i < (FT_UInt)globals->glyph_count; i++ )
      gstyles[i] = AF_STYLE_UNASSIGNED;

    error = FT_Select_Charmap( face, FT_ENCODING_UNICODE );
    if ( error )
    {
      /*
       * Ignore this error; we simply use the fallback style.
       * XXX: Shouldn't we rather disable hinting?
       */
      error = FT_Err_Ok;
      goto Exit;
    }

    /* scan each style in a Unicode charmap */
    for ( ss = 0; AF_STYLE_CLASSES_GET[ss]; ss++ )
    {
      AF_StyleClass       style_class =
                            AF_STYLE_CLASSES_GET[ss];
      AF_ScriptClass      script_class =
                            AF_SCRIPT_CLASSES_GET[style_class->script];
      AF_Script_UniRange  range;


      if ( !script_class->script_uni_ranges )
        continue;

      /*
       *  Scan all Unicode points in the range and set the corresponding
       *  glyph style index.
       */
      if ( style_class->coverage == AF_COVERAGE_DEFAULT )
      {
        if ( (FT_UInt)style_class->script ==
             globals->module->default_script )
          dflt = ss;

        for ( range = script_class->script_uni_ranges;
              range->first != 0;
              range++ )
        {
          FT_ULong  charcode = range->first;
          FT_UInt   gindex;


          gindex = FT_Get_Char_Index( face, charcode );

          if ( gindex != 0                                                &&
               gindex < (FT_ULong)globals->glyph_count                    &&
               ( gstyles[gindex] & AF_STYLE_MASK ) == AF_STYLE_UNASSIGNED )
            gstyles[gindex] = (FT_UShort)ss;

          for (;;)
          {
            charcode = FT_Get_Next_Char( face, charcode, &gindex );

            if ( gindex == 0 || charcode > range->last )
              break;

            if ( gindex < (FT_ULong)globals->glyph_count                    &&
                 ( gstyles[gindex] & AF_STYLE_MASK ) == AF_STYLE_UNASSIGNED )
              gstyles[gindex] = (FT_UShort)ss;
          }
        }

        /* do the same for the script's non-base characters */
        for ( range = script_class->script_uni_nonbase_ranges;
              range->first != 0;
              range++ )
        {
          FT_ULong  charcode = range->first;
          FT_UInt   gindex;


          gindex = FT_Get_Char_Index( face, charcode );

          if ( gindex != 0                                          &&
               gindex < (FT_ULong)globals->glyph_count              &&
               ( gstyles[gindex] & AF_STYLE_MASK ) == (FT_UShort)ss )
            gstyles[gindex] |= AF_NONBASE;

          for (;;)
          {
            charcode = FT_Get_Next_Char( face, charcode, &gindex );

            if ( gindex == 0 || charcode > range->last )
              break;

            if ( gindex < (FT_ULong)globals->glyph_count              &&
                 ( gstyles[gindex] & AF_STYLE_MASK ) == (FT_UShort)ss )
              gstyles[gindex] |= AF_NONBASE;
          }
        }
      }
      else
      {
        /* get glyphs not directly addressable by cmap */
        af_shaper_get_coverage( globals, style_class, gstyles, 0 );
      }
    }

    /* handle the remaining default OpenType features ... */
    for ( ss = 0; AF_STYLE_CLASSES_GET[ss]; ss++ )
    {
      AF_StyleClass  style_class = AF_STYLE_CLASSES_GET[ss];


      if ( style_class->coverage == AF_COVERAGE_DEFAULT )
        af_shaper_get_coverage( globals, style_class, gstyles, 0 );
    }

    /* ... and finally the default OpenType features of the default script */
    af_shaper_get_coverage( globals, AF_STYLE_CLASSES_GET[dflt], gstyles, 1 );

    /* mark ASCII digits */
    for ( i = 0x30; i <= 0x39; i++ )
    {
      FT_UInt  gindex = FT_Get_Char_Index( face, i );


      if ( gindex != 0 && gindex < (FT_ULong)globals->glyph_count )
        gstyles[gindex] |= AF_DIGIT;
    }

  Exit:
    /*
     *  By default, all uncovered glyphs are set to the fallback style.
     *  XXX: Shouldn't we disable hinting or do something similar?
     */
    if ( globals->module->fallback_style != AF_STYLE_UNASSIGNED )
    {
      FT_Long  nn;


      for ( nn = 0; nn < globals->glyph_count; nn++ )
      {
        if ( ( gstyles[nn] & AF_STYLE_MASK ) == AF_STYLE_UNASSIGNED )
        {
          gstyles[nn] &= ~AF_STYLE_MASK;
          gstyles[nn] |= globals->module->fallback_style;
        }
      }
    }

#ifdef FT_DEBUG_LEVEL_TRACE

    FT_TRACE4(( "\n"
                "style coverage\n"
                "==============\n"
                "\n" ));

    for ( ss = 0; AF_STYLE_CLASSES_GET[ss]; ss++ )
    {
      AF_StyleClass  style_class = AF_STYLE_CLASSES_GET[ss];
      FT_UInt        count       = 0;
      FT_Long        idx;


      FT_TRACE4(( "%s:\n", af_style_names[style_class->style] ));

      for ( idx = 0; idx < globals->glyph_count; idx++ )
      {
        if ( ( gstyles[idx] & AF_STYLE_MASK ) == style_class->style )
        {
          if ( !( count % 10 ) )
            FT_TRACE4(( " " ));

          FT_TRACE4(( " %d", idx ));
          count++;

          if ( !( count % 10 ) )
            FT_TRACE4(( "\n" ));
        }
      }

      if ( !count )
        FT_TRACE4(( "  (none)\n" ));
      if ( count % 10 )
        FT_TRACE4(( "\n" ));
    }

#endif /* FT_DEBUG_LEVEL_TRACE */

    FT_Set_Charmap( face, old_charmap );
    return error;
  }