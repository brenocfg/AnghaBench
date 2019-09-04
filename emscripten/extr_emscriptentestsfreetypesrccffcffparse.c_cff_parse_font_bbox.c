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
struct TYPE_5__ {void* yMax; void* xMax; void* yMin; void* xMin; } ;
struct TYPE_7__ {TYPE_1__ font_bbox; } ;
struct TYPE_6__ {int /*<<< orphan*/ ** stack; int /*<<< orphan*/ ** top; int /*<<< orphan*/  object; } ;
typedef  int /*<<< orphan*/  FT_Error ;
typedef  int /*<<< orphan*/  FT_Byte ;
typedef  TYPE_1__ FT_BBox ;
typedef  TYPE_2__* CFF_Parser ;
typedef  TYPE_3__* CFF_FontRecDict ;

/* Variables and functions */
 int /*<<< orphan*/  CFF_Err_Ok ; 
 int /*<<< orphan*/  CFF_Err_Stack_Underflow ; 
 void* FT_RoundFix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cff_parse_fixed (int /*<<< orphan*/ **) ; 

__attribute__((used)) static FT_Error
  cff_parse_font_bbox( CFF_Parser  parser )
  {
    CFF_FontRecDict  dict = (CFF_FontRecDict)parser->object;
    FT_BBox*         bbox = &dict->font_bbox;
    FT_Byte**        data = parser->stack;
    FT_Error         error;


    error = CFF_Err_Stack_Underflow;

    if ( parser->top >= parser->stack + 4 )
    {
      bbox->xMin = FT_RoundFix( cff_parse_fixed( data++ ) );
      bbox->yMin = FT_RoundFix( cff_parse_fixed( data++ ) );
      bbox->xMax = FT_RoundFix( cff_parse_fixed( data++ ) );
      bbox->yMax = FT_RoundFix( cff_parse_fixed( data   ) );
      error = CFF_Err_Ok;
    }

    return error;
  }