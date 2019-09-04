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
  gxv_kern_coverage_classic_microsoft_validate( FT_UShort      coverage,
                                                FT_UShort*     format,
                                                GXV_Validator  valid )
  {
    /* classic Microsoft-dialect */
    FT_Bool  horizontal;
    FT_Bool  minimum;
    FT_Bool  cross_stream;
    FT_Bool  override;

    FT_UNUSED( valid );


    /* reserved bits = 0 */
    if ( coverage & 0xFDF0 )
      return 0;

    horizontal   = FT_BOOL(   coverage        & 1 );
    minimum      = FT_BOOL( ( coverage >> 1 ) & 1 );
    cross_stream = FT_BOOL( ( coverage >> 2 ) & 1 );
    override     = FT_BOOL( ( coverage >> 3 ) & 1 );

    *format = (FT_UShort)( ( coverage >> 8 ) & 0x0003 );

    GXV_TRACE(( "classic Microsoft-dialect: "
                "horizontal=%d, minimum=%d, cross-stream=%d, "
                "override=%d, format=%d\n",
                horizontal, minimum, cross_stream, override, *format ));

    if ( *format == 2 )
      GXV_TRACE((
        "kerning values in Microsoft format 2 subtable are ignored\n" ));

    return 1;
  }