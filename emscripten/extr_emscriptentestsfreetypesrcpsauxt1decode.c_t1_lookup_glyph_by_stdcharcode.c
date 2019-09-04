#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__* (* adobe_std_strings ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/ * adobe_std_encoding; } ;
struct TYPE_4__ {size_t num_glyphs; scalar_t__* glyph_names; TYPE_2__* psnames; } ;
typedef  TYPE_1__* T1_Decoder ;
typedef  size_t FT_UInt ;
typedef  scalar_t__ const FT_String ;
typedef  TYPE_2__* FT_Service_PsCMaps ;
typedef  int FT_Int ;

/* Variables and functions */
 scalar_t__ ft_strcmp (scalar_t__ const*,scalar_t__ const*) ; 
 scalar_t__* stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static FT_Int
  t1_lookup_glyph_by_stdcharcode( T1_Decoder  decoder,
                                  FT_Int      charcode )
  {
    FT_UInt             n;
    const FT_String*    glyph_name;
    FT_Service_PsCMaps  psnames = decoder->psnames;


    /* check range of standard char code */
    if ( charcode < 0 || charcode > 255 )
      return -1;

    glyph_name = psnames->adobe_std_strings(
                   psnames->adobe_std_encoding[charcode]);

    for ( n = 0; n < decoder->num_glyphs; n++ )
    {
      FT_String*  name = (FT_String*)decoder->glyph_names[n];


      if ( name                               &&
           name[0] == glyph_name[0]           &&
           ft_strcmp( name, glyph_name ) == 0 )
        return n;
    }

    return -1;
  }