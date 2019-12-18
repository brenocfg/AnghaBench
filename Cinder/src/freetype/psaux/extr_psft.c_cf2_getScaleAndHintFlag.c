#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* glyph; } ;
struct TYPE_7__ {TYPE_1__ builder; } ;
struct TYPE_6__ {int /*<<< orphan*/  y_scale; int /*<<< orphan*/  x_scale; scalar_t__ scaled; scalar_t__ hint; } ;
typedef  TYPE_3__ PS_Decoder ;
typedef  scalar_t__ FT_Bool ;
typedef  int CF2_Fixed ;

/* Variables and functions */
 int ADD_INT32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FT_ASSERT (int) ; 

__attribute__((used)) static void
  cf2_getScaleAndHintFlag( PS_Decoder*  decoder,
                           CF2_Fixed*   x_scale,
                           CF2_Fixed*   y_scale,
                           FT_Bool*     hinted,
                           FT_Bool*     scaled )
  {
    FT_ASSERT( decoder && decoder->builder.glyph );

    /* note: FreeType scale includes a factor of 64 */
    *hinted = decoder->builder.glyph->hint;
    *scaled = decoder->builder.glyph->scaled;

    if ( *hinted )
    {
      *x_scale = ADD_INT32( decoder->builder.glyph->x_scale, 32 ) / 64;
      *y_scale = ADD_INT32( decoder->builder.glyph->y_scale, 32 ) / 64;
    }
    else
    {
      /* for unhinted outlines, `cff_slot_load' does the scaling, */
      /* thus render at `unity' scale                             */

      *x_scale = 0x0400;   /* 1/64 as 16.16 */
      *y_scale = 0x0400;
    }
  }