#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  x; scalar_t__ y; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* get_kerning ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  sfnt; } ;
typedef  TYPE_1__* TT_Face ;
typedef  TYPE_2__* SFNT_Service ;
typedef  TYPE_3__ FT_Vector ;
typedef  int /*<<< orphan*/  FT_UInt ;
typedef  int /*<<< orphan*/  FT_Face ;
typedef  int /*<<< orphan*/  FT_Error ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static FT_Error
  tt_get_kerning( FT_Face     ttface,          /* TT_Face */
                  FT_UInt     left_glyph,
                  FT_UInt     right_glyph,
                  FT_Vector*  kerning )
  {
    TT_Face       face = (TT_Face)ttface;
    SFNT_Service  sfnt = (SFNT_Service)face->sfnt;


    kerning->x = 0;
    kerning->y = 0;

    if ( sfnt )
      kerning->x = sfnt->get_kerning( face, left_glyph, right_glyph );

    return 0;
  }