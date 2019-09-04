#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* y; void* x; } ;
struct TYPE_7__ {int xx; int yy; void* xy; void* yx; } ;
struct TYPE_9__ {int units_per_em; TYPE_1__ font_offset; TYPE_2__ font_matrix; } ;
struct TYPE_8__ {int /*<<< orphan*/ ** stack; int /*<<< orphan*/ ** top; int /*<<< orphan*/  object; } ;
typedef  TYPE_1__ FT_Vector ;
typedef  int FT_ULong ;
typedef  TYPE_2__ FT_Matrix ;
typedef  int FT_Long ;
typedef  int /*<<< orphan*/  FT_Error ;
typedef  int /*<<< orphan*/  FT_Byte ;
typedef  TYPE_3__* CFF_Parser ;
typedef  TYPE_4__* CFF_FontRecDict ;

/* Variables and functions */
 int /*<<< orphan*/  CFF_Err_Ok ; 
 int /*<<< orphan*/  CFF_Err_Stack_Underflow ; 
 int cff_parse_fixed_dynamic (int /*<<< orphan*/ ,int*) ; 
 void* cff_parse_fixed_scaled (int /*<<< orphan*/ **,int) ; 
 int* power_tens ; 

__attribute__((used)) static FT_Error
  cff_parse_font_matrix( CFF_Parser  parser )
  {
    CFF_FontRecDict  dict   = (CFF_FontRecDict)parser->object;
    FT_Matrix*       matrix = &dict->font_matrix;
    FT_Vector*       offset = &dict->font_offset;
    FT_ULong*        upm    = &dict->units_per_em;
    FT_Byte**        data   = parser->stack;
    FT_Error         error  = CFF_Err_Stack_Underflow;


    if ( parser->top >= parser->stack + 6 )
    {
      FT_Long  scaling;


      error = CFF_Err_Ok;

      /* We expect a well-formed font matrix, this is, the matrix elements */
      /* `xx' and `yy' are of approximately the same magnitude.  To avoid  */
      /* loss of precision, we use the magnitude of element `xx' to scale  */
      /* all other elements.  The scaling factor is then contained in the  */
      /* `units_per_em' value.                                             */

      matrix->xx = cff_parse_fixed_dynamic( data++, &scaling );

      scaling = -scaling;

      if ( scaling < 0 || scaling > 9 )
      {
        /* Return default matrix in case of unlikely values. */
        matrix->xx = 0x10000L;
        matrix->yx = 0;
        matrix->yx = 0;
        matrix->yy = 0x10000L;
        offset->x  = 0;
        offset->y  = 0;
        *upm       = 1;

        goto Exit;
      }

      matrix->yx = cff_parse_fixed_scaled( data++, scaling );
      matrix->xy = cff_parse_fixed_scaled( data++, scaling );
      matrix->yy = cff_parse_fixed_scaled( data++, scaling );
      offset->x  = cff_parse_fixed_scaled( data++, scaling );
      offset->y  = cff_parse_fixed_scaled( data,   scaling );

      *upm = power_tens[scaling];
    }

  Exit:
    return error;
  }