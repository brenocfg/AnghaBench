#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ count; TYPE_2__* zones; } ;
struct TYPE_9__ {scalar_t__ org_ref; scalar_t__ org_delta; scalar_t__ org_bottom; scalar_t__ org_top; } ;
struct TYPE_8__ {TYPE_3__ normal_bottom; TYPE_3__ normal_top; TYPE_3__ family_bottom; TYPE_3__ family_top; } ;
typedef  TYPE_1__* PSH_Blues ;
typedef  TYPE_2__* PSH_Blue_Zone ;
typedef  TYPE_3__* PSH_Blue_Table ;
typedef  scalar_t__ FT_UInt ;
typedef  int /*<<< orphan*/  FT_Short ;
typedef  scalar_t__ FT_Int ;

/* Variables and functions */
 int /*<<< orphan*/  psh_blues_set_zones_0 (TYPE_1__*,int,scalar_t__,int /*<<< orphan*/ *,TYPE_3__*,TYPE_3__*) ; 

__attribute__((used)) static void
  psh_blues_set_zones( PSH_Blues  target,
                       FT_UInt    count,
                       FT_Short*  blues,
                       FT_UInt    count_others,
                       FT_Short*  other_blues,
                       FT_Int     fuzz,
                       FT_Int     family )
  {
    PSH_Blue_Table  top_table, bot_table;
    FT_UInt         count_top, count_bot;


    if ( family )
    {
      top_table = &target->family_top;
      bot_table = &target->family_bottom;
    }
    else
    {
      top_table = &target->normal_top;
      bot_table = &target->normal_bottom;
    }

    /* read the input blue zones, and build two sorted tables  */
    /* (one for the top zones, the other for the bottom zones) */
    top_table->count = 0;
    bot_table->count = 0;

    /* first, the blues */
    psh_blues_set_zones_0( target, 0,
                           count, blues, top_table, bot_table );
    psh_blues_set_zones_0( target, 1,
                           count_others, other_blues, top_table, bot_table );

    count_top = top_table->count;
    count_bot = bot_table->count;

    /* sanitize top table */
    if ( count_top > 0 )
    {
      PSH_Blue_Zone  zone = top_table->zones;


      for ( count = count_top; count > 0; count--, zone++ )
      {
        FT_Int  delta;


        if ( count > 1 )
        {
          delta = zone[1].org_ref - zone[0].org_ref;
          if ( zone->org_delta > delta )
            zone->org_delta = delta;
        }

        zone->org_bottom = zone->org_ref;
        zone->org_top    = zone->org_delta + zone->org_ref;
      }
    }

    /* sanitize bottom table */
    if ( count_bot > 0 )
    {
      PSH_Blue_Zone  zone = bot_table->zones;


      for ( count = count_bot; count > 0; count--, zone++ )
      {
        FT_Int  delta;


        if ( count > 1 )
        {
          delta = zone[0].org_ref - zone[1].org_ref;
          if ( zone->org_delta < delta )
            zone->org_delta = delta;
        }

        zone->org_top    = zone->org_ref;
        zone->org_bottom = zone->org_delta + zone->org_ref;
      }
    }

    /* expand top and bottom tables with blue fuzz */
    {
      FT_Int         dim, top, bot, delta;
      PSH_Blue_Zone  zone;


      zone  = top_table->zones;
      count = count_top;

      for ( dim = 1; dim >= 0; dim-- )
      {
        if ( count > 0 )
        {
          /* expand the bottom of the lowest zone normally */
          zone->org_bottom -= fuzz;

          /* expand the top and bottom of intermediate zones;    */
          /* checking that the interval is smaller than the fuzz */
          top = zone->org_top;

          for ( count--; count > 0; count-- )
          {
            bot   = zone[1].org_bottom;
            delta = bot - top;

            if ( delta / 2 < fuzz )
              zone[0].org_top = zone[1].org_bottom = top + delta / 2;
            else
            {
              zone[0].org_top    = top + fuzz;
              zone[1].org_bottom = bot - fuzz;
            }

            zone++;
            top = zone->org_top;
          }

          /* expand the top of the highest zone normally */
          zone->org_top = top + fuzz;
        }
        zone  = bot_table->zones;
        count = count_bot;
      }
    }
  }