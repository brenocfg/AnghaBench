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
typedef  scalar_t__ FT_Bool ;
typedef  scalar_t__ CF2_UInt ;
typedef  int /*<<< orphan*/  CF2_Stack ;
typedef  int CF2_Int ;
typedef  int /*<<< orphan*/  CF2_GlyphPath ;
typedef  int /*<<< orphan*/  CF2_Fixed ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_INT32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ const FALSE ; 
 scalar_t__ FT_BOOL (int) ; 
 int /*<<< orphan*/  SUB_INT32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cf2_fixedAbs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cf2_glyphpath_curveTo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cf2_stack_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cf2_stack_getReal (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
  cf2_doFlex( CF2_Stack       opStack,
              CF2_Fixed*      curX,
              CF2_Fixed*      curY,
              CF2_GlyphPath   glyphPath,
              const FT_Bool*  readFromStack,
              FT_Bool         doConditionalLastRead )
  {
    CF2_Fixed  vals[14];
    CF2_UInt   idx;
    FT_Bool    isHFlex;
    CF2_Int    top, i, j;


    vals[0] = *curX;
    vals[1] = *curY;
    idx     = 0;
    isHFlex = FT_BOOL( readFromStack[9] == FALSE );
    top     = isHFlex ? 9 : 10;

    for ( i = 0; i < top; i++ )
    {
      vals[i + 2] = vals[i];
      if ( readFromStack[i] )
        vals[i + 2] = ADD_INT32( vals[i + 2], cf2_stack_getReal( opStack,
                                                                 idx++ ) );
    }

    if ( isHFlex )
      vals[9 + 2] = *curY;

    if ( doConditionalLastRead )
    {
      FT_Bool    lastIsX = (FT_Bool)(
                             cf2_fixedAbs( SUB_INT32( vals[10], *curX ) ) >
                             cf2_fixedAbs( SUB_INT32( vals[11], *curY ) ) );
      CF2_Fixed  lastVal = cf2_stack_getReal( opStack, idx );


      if ( lastIsX )
      {
        vals[12] = ADD_INT32( vals[10], lastVal );
        vals[13] = *curY;
      }
      else
      {
        vals[12] = *curX;
        vals[13] = ADD_INT32( vals[11], lastVal );
      }
    }
    else
    {
      if ( readFromStack[10] )
        vals[12] = ADD_INT32( vals[10],
                              cf2_stack_getReal( opStack, idx++ ) );
      else
        vals[12] = *curX;

      if ( readFromStack[11] )
        vals[13] = ADD_INT32( vals[11],
                              cf2_stack_getReal( opStack, idx ) );
      else
        vals[13] = *curY;
    }

    for ( j = 0; j < 2; j++ )
      cf2_glyphpath_curveTo( glyphPath, vals[j * 6 + 2],
                                        vals[j * 6 + 3],
                                        vals[j * 6 + 4],
                                        vals[j * 6 + 5],
                                        vals[j * 6 + 6],
                                        vals[j * 6 + 7] );

    cf2_stack_clear( opStack );

    *curX = vals[12];
    *curY = vals[13];
  }