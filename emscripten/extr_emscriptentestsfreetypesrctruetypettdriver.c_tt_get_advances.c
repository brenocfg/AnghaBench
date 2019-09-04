#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  TT_Face ;
typedef  int /*<<< orphan*/  FT_UShort ;
typedef  scalar_t__ FT_UInt ;
typedef  int /*<<< orphan*/  FT_Short ;
typedef  int FT_Int32 ;
typedef  int /*<<< orphan*/  FT_Fixed ;
typedef  int /*<<< orphan*/  FT_Face ;
typedef  int /*<<< orphan*/  FT_Error ;
typedef  int /*<<< orphan*/  FT_Bool ;

/* Variables and functions */
 int /*<<< orphan*/  FT_BOOL (int) ; 
 int FT_LOAD_IGNORE_GLOBAL_ADVANCE_WIDTH ; 
 int FT_LOAD_VERTICAL_LAYOUT ; 
 int /*<<< orphan*/  TT_Err_Ok ; 
 int /*<<< orphan*/  TT_Get_HMetrics (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TT_Get_VMetrics (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static FT_Error
  tt_get_advances( FT_Face    ttface,
                   FT_UInt    start,
                   FT_UInt    count,
                   FT_Int32   flags,
                   FT_Fixed  *advances )
  {
    FT_UInt  nn;
    TT_Face  face  = (TT_Face) ttface;
    FT_Bool  check = FT_BOOL(
                       !( flags & FT_LOAD_IGNORE_GLOBAL_ADVANCE_WIDTH ) );


    /* XXX: TODO: check for sbits */

    if ( flags & FT_LOAD_VERTICAL_LAYOUT )
    {
      for ( nn = 0; nn < count; nn++ )
      {
        FT_Short   tsb;
        FT_UShort  ah;


        TT_Get_VMetrics( face, start + nn, check, &tsb, &ah );
        advances[nn] = ah;
      }
    }
    else
    {
      for ( nn = 0; nn < count; nn++ )
      {
        FT_Short   lsb;
        FT_UShort  aw;


        TT_Get_HMetrics( face, start + nn, check, &lsb, &aw );
        advances[nn] = aw;
      }
    }

    return TT_Err_Ok;
  }