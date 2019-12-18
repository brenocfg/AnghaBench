#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* atom; } ;
struct TYPE_10__ {scalar_t__ format; TYPE_1__ value; } ;
typedef  TYPE_2__ bdf_property_t ;
typedef  int /*<<< orphan*/  bdf_font_t ;
struct TYPE_12__ {int /*<<< orphan*/ * bdffont; } ;
struct TYPE_11__ {char* style_name; int /*<<< orphan*/  style_flags; int /*<<< orphan*/  memory; } ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  TYPE_3__* FT_Face ;
typedef  int /*<<< orphan*/  FT_Error ;
typedef  TYPE_4__* BDF_Face ;

/* Variables and functions */
 scalar_t__ BDF_ATOM ; 
 scalar_t__ FT_ALLOC (char*,size_t) ; 
 int /*<<< orphan*/  FT_Err_Ok ; 
 TYPE_3__* FT_FACE (TYPE_4__*) ; 
 int /*<<< orphan*/  FT_STYLE_FLAG_BOLD ; 
 int /*<<< orphan*/  FT_STYLE_FLAG_ITALIC ; 
 TYPE_2__* bdf_get_font_property (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ft_memcpy (char*,char*,size_t) ; 
 size_t ft_strlen (char*) ; 

__attribute__((used)) static FT_Error
  bdf_interpret_style( BDF_Face  bdf )
  {
    FT_Error         error  = FT_Err_Ok;
    FT_Face          face   = FT_FACE( bdf );
    FT_Memory        memory = face->memory;
    bdf_font_t*      font   = bdf->bdffont;
    bdf_property_t*  prop;

    char*   strings[4] = { NULL, NULL, NULL, NULL };
    size_t  nn, len, lengths[4];


    face->style_flags = 0;

    prop = bdf_get_font_property( font, (char *)"SLANT" );
    if ( prop && prop->format == BDF_ATOM                             &&
         prop->value.atom                                             &&
         ( *(prop->value.atom) == 'O' || *(prop->value.atom) == 'o' ||
           *(prop->value.atom) == 'I' || *(prop->value.atom) == 'i' ) )
    {
      face->style_flags |= FT_STYLE_FLAG_ITALIC;
      strings[2] = ( *(prop->value.atom) == 'O' || *(prop->value.atom) == 'o' )
                   ? (char *)"Oblique"
                   : (char *)"Italic";
    }

    prop = bdf_get_font_property( font, (char *)"WEIGHT_NAME" );
    if ( prop && prop->format == BDF_ATOM                             &&
         prop->value.atom                                             &&
         ( *(prop->value.atom) == 'B' || *(prop->value.atom) == 'b' ) )
    {
      face->style_flags |= FT_STYLE_FLAG_BOLD;
      strings[1] = (char *)"Bold";
    }

    prop = bdf_get_font_property( font, (char *)"SETWIDTH_NAME" );
    if ( prop && prop->format == BDF_ATOM                              &&
         prop->value.atom && *(prop->value.atom)                       &&
         !( *(prop->value.atom) == 'N' || *(prop->value.atom) == 'n' ) )
      strings[3] = (char *)(prop->value.atom);

    prop = bdf_get_font_property( font, (char *)"ADD_STYLE_NAME" );
    if ( prop && prop->format == BDF_ATOM                              &&
         prop->value.atom && *(prop->value.atom)                       &&
         !( *(prop->value.atom) == 'N' || *(prop->value.atom) == 'n' ) )
      strings[0] = (char *)(prop->value.atom);

    for ( len = 0, nn = 0; nn < 4; nn++ )
    {
      lengths[nn] = 0;
      if ( strings[nn] )
      {
        lengths[nn] = ft_strlen( strings[nn] );
        len        += lengths[nn] + 1;
      }
    }

    if ( len == 0 )
    {
      strings[0] = (char *)"Regular";
      lengths[0] = ft_strlen( strings[0] );
      len        = lengths[0] + 1;
    }

    {
      char*  s;


      if ( FT_ALLOC( face->style_name, len ) )
        return error;

      s = face->style_name;

      for ( nn = 0; nn < 4; nn++ )
      {
        char*  src = strings[nn];


        len = lengths[nn];

        if ( !src )
          continue;

        /* separate elements with a space */
        if ( s != face->style_name )
          *s++ = ' ';

        ft_memcpy( s, src, len );

        /* need to convert spaces to dashes for */
        /* add_style_name and setwidth_name     */
        if ( nn == 0 || nn == 3 )
        {
          size_t  mm;


          for ( mm = 0; mm < len; mm++ )
            if ( s[mm] == ' ' )
              s[mm] = '-';
        }

        s += len;
      }
      *s = 0;
    }

    return error;
  }