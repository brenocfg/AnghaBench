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
struct TYPE_5__ {void* private_offset; void* private_size; } ;
struct TYPE_4__ {int /*<<< orphan*/ ** stack; int /*<<< orphan*/ ** top; int /*<<< orphan*/  object; } ;
typedef  int /*<<< orphan*/  FT_Error ;
typedef  int /*<<< orphan*/  FT_Byte ;
typedef  TYPE_1__* CFF_Parser ;
typedef  TYPE_2__* CFF_FontRecDict ;

/* Variables and functions */
 int /*<<< orphan*/  CFF_Err_Ok ; 
 int /*<<< orphan*/  CFF_Err_Stack_Underflow ; 
 void* cff_parse_num (int /*<<< orphan*/ **) ; 

__attribute__((used)) static FT_Error
  cff_parse_private_dict( CFF_Parser  parser )
  {
    CFF_FontRecDict  dict = (CFF_FontRecDict)parser->object;
    FT_Byte**        data = parser->stack;
    FT_Error         error;


    error = CFF_Err_Stack_Underflow;

    if ( parser->top >= parser->stack + 2 )
    {
      dict->private_size   = cff_parse_num( data++ );
      dict->private_offset = cff_parse_num( data   );
      error = CFF_Err_Ok;
    }

    return error;
  }