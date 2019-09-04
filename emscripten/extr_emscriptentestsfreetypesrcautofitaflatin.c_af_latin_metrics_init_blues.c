#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {size_t blue_count; TYPE_8__* blues; } ;
struct TYPE_16__ {scalar_t__ org; } ;
struct TYPE_15__ {scalar_t__ org; } ;
struct TYPE_21__ {int /*<<< orphan*/  flags; TYPE_3__ shoot; TYPE_2__ ref; } ;
struct TYPE_20__ {TYPE_9__* axis; } ;
struct TYPE_19__ {TYPE_5__* glyph; } ;
struct TYPE_14__ {scalar_t__ n_points; size_t n_contours; size_t* contours; int /*<<< orphan*/ * tags; TYPE_4__* points; } ;
struct TYPE_18__ {TYPE_1__ outline; } ;
struct TYPE_17__ {scalar_t__ y; } ;
typedef  TYPE_4__ FT_Vector ;
typedef  scalar_t__ FT_UInt ;
typedef  scalar_t__ FT_Pos ;
typedef  size_t FT_Int ;
typedef  TYPE_5__* FT_GlyphSlot ;
typedef  TYPE_6__* FT_Face ;
typedef  scalar_t__ FT_Error ;
typedef  int FT_Bool ;
typedef  TYPE_7__* AF_LatinMetrics ;
typedef  TYPE_8__* AF_LatinBlue ;
typedef  TYPE_9__* AF_LatinAxis ;

/* Variables and functions */
 size_t AF_DIMENSION_VERT ; 
 int /*<<< orphan*/  AF_LATIN_BLUE_ADJUSTMENT ; 
 size_t AF_LATIN_BLUE_MAX ; 
 size_t AF_LATIN_BLUE_SMALL_TOP ; 
 int /*<<< orphan*/  AF_LATIN_BLUE_TOP ; 
 int AF_LATIN_IS_TOP_BLUE (size_t) ; 
 int AF_LATIN_MAX_TEST_CHARACTERS ; 
 int /*<<< orphan*/  AF_LOG (char*) ; 
 int FT_BOOL (int) ; 
 scalar_t__ FT_CURVE_TAG (int /*<<< orphan*/ ) ; 
 scalar_t__ FT_CURVE_TAG_ON ; 
 scalar_t__ FT_Get_Char_Index (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  FT_LOAD_NO_SCALE ; 
 scalar_t__ FT_Load_Glyph (TYPE_6__*,scalar_t__,int /*<<< orphan*/ ) ; 
 char** af_latin_blue_chars ; 
 int /*<<< orphan*/  af_sort_pos (size_t,scalar_t__*) ; 

__attribute__((used)) static void
  af_latin_metrics_init_blues( AF_LatinMetrics  metrics,
                               FT_Face          face )
  {
    FT_Pos        flats [AF_LATIN_MAX_TEST_CHARACTERS];
    FT_Pos        rounds[AF_LATIN_MAX_TEST_CHARACTERS];
    FT_Int        num_flats;
    FT_Int        num_rounds;
    FT_Int        bb;
    AF_LatinBlue  blue;
    FT_Error      error;
    AF_LatinAxis  axis  = &metrics->axis[AF_DIMENSION_VERT];
    FT_GlyphSlot  glyph = face->glyph;


    /* we compute the blues simply by loading each character from the    */
    /* 'af_latin_blue_chars[blues]' string, then compute its top-most or */
    /* bottom-most points (depending on `AF_IS_TOP_BLUE')                */

    AF_LOG(( "blue zones computation\n" ));
    AF_LOG(( "------------------------------------------------\n" ));

    for ( bb = 0; bb < AF_LATIN_BLUE_MAX; bb++ )
    {
      const char*  p     = af_latin_blue_chars[bb];
      const char*  limit = p + AF_LATIN_MAX_TEST_CHARACTERS;
      FT_Pos*      blue_ref;
      FT_Pos*      blue_shoot;


      AF_LOG(( "blue %3d: ", bb ));

      num_flats  = 0;
      num_rounds = 0;

      for ( ; p < limit && *p; p++ )
      {
        FT_UInt     glyph_index;
        FT_Pos      best_y; /* same as points.y */
        FT_Int      best_point, best_first, best_last;
        FT_Vector*  points;
        FT_Bool     round = 0;


        AF_LOG(( "'%c'", *p ));

        /* load the character in the face -- skip unknown or empty ones */
        glyph_index = FT_Get_Char_Index( face, (FT_UInt)*p );
        if ( glyph_index == 0 )
          continue;

        error = FT_Load_Glyph( face, glyph_index, FT_LOAD_NO_SCALE );
        if ( error || glyph->outline.n_points <= 0 )
          continue;

        /* now compute min or max point indices and coordinates */
        points      = glyph->outline.points;
        best_point  = -1;
        best_y      = 0;  /* make compiler happy */
        best_first  = 0;  /* ditto */
        best_last   = 0;  /* ditto */

        {
          FT_Int  nn;
          FT_Int  first = 0;
          FT_Int  last  = -1;


          for ( nn = 0; nn < glyph->outline.n_contours; first = last+1, nn++ )
          {
            FT_Int  old_best_point = best_point;
            FT_Int  pp;


            last = glyph->outline.contours[nn];

            /* Avoid single-point contours since they are never rasterized. */
            /* In some fonts, they correspond to mark attachment points     */
            /* which are way outside of the glyph's real outline.           */
            if ( last <= first )
                continue;

            if ( AF_LATIN_IS_TOP_BLUE( bb ) )
            {
              for ( pp = first; pp <= last; pp++ )
                if ( best_point < 0 || points[pp].y > best_y )
                {
                  best_point = pp;
                  best_y     = points[pp].y;
                }
            }
            else
            {
              for ( pp = first; pp <= last; pp++ )
                if ( best_point < 0 || points[pp].y < best_y )
                {
                  best_point = pp;
                  best_y     = points[pp].y;
                }
            }

            if ( best_point != old_best_point )
            {
              best_first = first;
              best_last  = last;
            }
          }
          AF_LOG(( "%5d", best_y ));
        }

        /* now check whether the point belongs to a straight or round   */
        /* segment; we first need to find in which contour the extremum */
        /* lies, then inspect its previous and next points              */
        if ( best_point >= 0 )
        {
          FT_Int  prev, next;
          FT_Pos  dist;


          /* now look for the previous and next points that are not on the */
          /* same Y coordinate.  Threshold the `closeness'...              */
          prev = best_point;
          next = prev;

          do
          {
            if ( prev > best_first )
              prev--;
            else
              prev = best_last;

            dist = points[prev].y - best_y;
            if ( dist < -5 || dist > 5 )
              break;

          } while ( prev != best_point );

          do
          {
            if ( next < best_last )
              next++;
            else
              next = best_first;

            dist = points[next].y - best_y;
            if ( dist < -5 || dist > 5 )
              break;

          } while ( next != best_point );

          /* now, set the `round' flag depending on the segment's kind */
          round = FT_BOOL(
            FT_CURVE_TAG( glyph->outline.tags[prev] ) != FT_CURVE_TAG_ON ||
            FT_CURVE_TAG( glyph->outline.tags[next] ) != FT_CURVE_TAG_ON );

          AF_LOG(( "%c ", round ? 'r' : 'f' ));
        }

        if ( round )
          rounds[num_rounds++] = best_y;
        else
          flats[num_flats++]   = best_y;
      }

      AF_LOG(( "\n" ));

      if ( num_flats == 0 && num_rounds == 0 )
      {
        /*
         *  we couldn't find a single glyph to compute this blue zone,
         *  we will simply ignore it then
         */
        AF_LOG(( "empty\n" ));
        continue;
      }

      /* we have computed the contents of the `rounds' and `flats' tables, */
      /* now determine the reference and overshoot position of the blue -- */
      /* we simply take the median value after a simple sort               */
      af_sort_pos( num_rounds, rounds );
      af_sort_pos( num_flats,  flats );

      blue       = & axis->blues[axis->blue_count];
      blue_ref   = & blue->ref.org;
      blue_shoot = & blue->shoot.org;

      axis->blue_count++;

      if ( num_flats == 0 )
      {
        *blue_ref   =
        *blue_shoot = rounds[num_rounds / 2];
      }
      else if ( num_rounds == 0 )
      {
        *blue_ref   =
        *blue_shoot = flats[num_flats / 2];
      }
      else
      {
        *blue_ref   = flats[num_flats / 2];
        *blue_shoot = rounds[num_rounds / 2];
      }

      /* there are sometimes problems: if the overshoot position of top     */
      /* zones is under its reference position, or the opposite for bottom  */
      /* zones.  We must thus check everything there and correct the errors */
      if ( *blue_shoot != *blue_ref )
      {
        FT_Pos   ref      = *blue_ref;
        FT_Pos   shoot    = *blue_shoot;
        FT_Bool  over_ref = FT_BOOL( shoot > ref );


        if ( AF_LATIN_IS_TOP_BLUE( bb ) ^ over_ref )
          *blue_shoot = *blue_ref = ( shoot + ref ) / 2;
      }

      blue->flags = 0;
      if ( AF_LATIN_IS_TOP_BLUE( bb ) )
        blue->flags |= AF_LATIN_BLUE_TOP;

      /*
       * The following flag is used later to adjust the y and x scales
       * in order to optimize the pixel grid alignment of the top of small
       * letters.
       */
      if ( bb == AF_LATIN_BLUE_SMALL_TOP )
        blue->flags |= AF_LATIN_BLUE_ADJUSTMENT;

      AF_LOG(( "-- ref = %ld, shoot = %ld\n", *blue_ref, *blue_shoot ));
    }

    return;
  }