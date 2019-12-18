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
struct TYPE_7__ {TYPE_2__* size; } ;
struct TYPE_5__ {int /*<<< orphan*/  x_scale; int /*<<< orphan*/  y_scale; } ;
struct TYPE_6__ {TYPE_1__ metrics; } ;
typedef  size_t FT_UInt ;
typedef  int FT_Int32 ;
typedef  int /*<<< orphan*/  FT_Fixed ;
typedef  TYPE_3__* FT_Face ;
typedef  int /*<<< orphan*/  FT_Error ;

/* Variables and functions */
 int /*<<< orphan*/  FT_Err_Ok ; 
 int FT_LOAD_NO_SCALE ; 
 int FT_LOAD_VERTICAL_LAYOUT ; 
 int /*<<< orphan*/  FT_MulDiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FT_THROW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Invalid_Size_Handle ; 

__attribute__((used)) static FT_Error
  _ft_face_scale_advances( FT_Face    face,
                           FT_Fixed*  advances,
                           FT_UInt    count,
                           FT_Int32   flags )
  {
    FT_Fixed  scale;
    FT_UInt   nn;


    if ( flags & FT_LOAD_NO_SCALE )
      return FT_Err_Ok;

    if ( !face->size )
      return FT_THROW( Invalid_Size_Handle );

    if ( flags & FT_LOAD_VERTICAL_LAYOUT )
      scale = face->size->metrics.y_scale;
    else
      scale = face->size->metrics.x_scale;

    /* this must be the same scaling as to get linear{Hori,Vert}Advance */
    /* (see `FT_Load_Glyph' implementation in src/base/ftobjs.c)        */

    for ( nn = 0; nn < count; nn++ )
      advances[nn] = FT_MulDiv( advances[nn], scale, 64 );

    return FT_Err_Ok;
  }