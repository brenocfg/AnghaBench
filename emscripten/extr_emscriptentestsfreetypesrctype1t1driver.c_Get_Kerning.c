#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_6__ {scalar_t__ afm_data; } ;
typedef  TYPE_1__* T1_Face ;
typedef  TYPE_2__ FT_Vector ;
typedef  int /*<<< orphan*/  FT_UInt ;
typedef  int /*<<< orphan*/  FT_Error ;
typedef  int /*<<< orphan*/  AFM_FontInfo ;

/* Variables and functions */
 int /*<<< orphan*/  T1_Err_Ok ; 
 int /*<<< orphan*/  T1_Get_Kerning (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static FT_Error
  Get_Kerning( T1_Face     face,
               FT_UInt     left_glyph,
               FT_UInt     right_glyph,
               FT_Vector*  kerning )
  {
    kerning->x = 0;
    kerning->y = 0;

    if ( face->afm_data )
      T1_Get_Kerning( (AFM_FontInfo)face->afm_data,
                      left_glyph,
                      right_glyph,
                      kerning );

    return T1_Err_Ok;
  }