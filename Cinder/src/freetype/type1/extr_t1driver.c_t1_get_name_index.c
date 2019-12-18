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
struct TYPE_4__ {size_t num_glyphs; int /*<<< orphan*/ ** glyph_names; } ;
struct TYPE_5__ {TYPE_1__ type1; } ;
typedef  TYPE_2__* T1_Face ;
typedef  int /*<<< orphan*/  FT_UInt ;
typedef  int /*<<< orphan*/  FT_String ;
typedef  size_t FT_Int ;

/* Variables and functions */
 int /*<<< orphan*/  ft_strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static FT_UInt
  t1_get_name_index( T1_Face     face,
                     FT_String*  glyph_name )
  {
    FT_Int  i;


    for ( i = 0; i < face->type1.num_glyphs; i++ )
    {
      FT_String*  gname = face->type1.glyph_names[i];


      if ( !ft_strcmp( glyph_name, gname ) )
        return (FT_UInt)i;
    }

    return 0;
  }