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
typedef  int /*<<< orphan*/  GXV_Validator ;
typedef  int FT_UShort ;
typedef  int FT_Bool ;

/* Variables and functions */
 int FT_BOOL (int) ; 
 int /*<<< orphan*/  FT_UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GXV_TRACE (char*) ; 

__attribute__((used)) static FT_Bool
  gxv_kern_coverage_new_apple_validate( FT_UShort      coverage,
                                        FT_UShort*     format,
                                        GXV_Validator  valid )
  {
    /* new Apple-dialect */
    FT_Bool  kernVertical;
    FT_Bool  kernCrossStream;
    FT_Bool  kernVariation;

    FT_UNUSED( valid );


    /* reserved bits = 0 */
    if ( coverage & 0x1FFC )
      return 0;

    kernVertical    = FT_BOOL( ( coverage >> 15 ) & 1 );
    kernCrossStream = FT_BOOL( ( coverage >> 14 ) & 1 );
    kernVariation   = FT_BOOL( ( coverage >> 13 ) & 1 );

    *format = (FT_UShort)( coverage & 0x0003 );

    GXV_TRACE(( "new Apple-dialect: "
                "horizontal=%d, cross-stream=%d, variation=%d, format=%d\n",
                 !kernVertical, kernCrossStream, kernVariation, *format ));

    GXV_TRACE(( "kerning values in Apple format subtable are ignored\n" ));

    return 1;
  }