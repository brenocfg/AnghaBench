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
struct TYPE_5__ {scalar_t__ cid_supplement; void* cid_ordering; void* cid_registry; } ;
struct TYPE_4__ {int** stack; int** top; int /*<<< orphan*/  object; } ;
typedef  void* FT_UInt ;
typedef  int /*<<< orphan*/  FT_Error ;
typedef  int FT_Byte ;
typedef  TYPE_1__* CFF_Parser ;
typedef  TYPE_2__* CFF_FontRecDict ;

/* Variables and functions */
 int /*<<< orphan*/  CFF_Err_Ok ; 
 int /*<<< orphan*/  CFF_Err_Stack_Underflow ; 
 int /*<<< orphan*/  FT_TRACE1 (char*) ; 
 scalar_t__ cff_parse_num (int**) ; 

__attribute__((used)) static FT_Error
  cff_parse_cid_ros( CFF_Parser  parser )
  {
    CFF_FontRecDict  dict = (CFF_FontRecDict)parser->object;
    FT_Byte**        data = parser->stack;
    FT_Error         error;


    error = CFF_Err_Stack_Underflow;

    if ( parser->top >= parser->stack + 3 )
    {
      dict->cid_registry   = (FT_UInt)cff_parse_num ( data++ );
      dict->cid_ordering   = (FT_UInt)cff_parse_num ( data++ );
      if ( **data == 30 )
        FT_TRACE1(( "cff_parse_cid_ros: real supplement is rounded\n" ));
      dict->cid_supplement = cff_parse_num( data );
      if ( dict->cid_supplement < 0 )
        FT_TRACE1(( "cff_parse_cid_ros: negative supplement %d is found\n",
                   dict->cid_supplement ));
      error = CFF_Err_Ok;
    }

    return error;
  }