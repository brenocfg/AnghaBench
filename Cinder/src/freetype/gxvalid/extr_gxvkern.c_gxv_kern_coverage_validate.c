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
typedef  int /*<<< orphan*/  GXV_kern_Dialect ;
typedef  int /*<<< orphan*/  GXV_Validator ;
typedef  int /*<<< orphan*/  FT_UShort ;

/* Variables and functions */
 int /*<<< orphan*/  GXV_EXIT ; 
 int /*<<< orphan*/  GXV_NAME_ENTER (char*) ; 
 int /*<<< orphan*/  GXV_TRACE (char*) ; 
 scalar_t__ KERN_ALLOWS_APPLE (int /*<<< orphan*/ ) ; 
 scalar_t__ KERN_ALLOWS_MS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_DIALECT_APPLE ; 
 int /*<<< orphan*/  KERN_DIALECT_MS ; 
 int /*<<< orphan*/  KERN_DIALECT_UNKNOWN ; 
 scalar_t__ KERN_IS_CLASSIC (int /*<<< orphan*/ ) ; 
 scalar_t__ KERN_IS_NEW (int /*<<< orphan*/ ) ; 
 scalar_t__ gxv_kern_coverage_classic_apple_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ gxv_kern_coverage_classic_microsoft_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ gxv_kern_coverage_new_apple_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static GXV_kern_Dialect
  gxv_kern_coverage_validate( FT_UShort      coverage,
                              FT_UShort*     format,
                              GXV_Validator  gxvalid )
  {
    GXV_kern_Dialect  result = KERN_DIALECT_UNKNOWN;


    GXV_NAME_ENTER( "validating coverage" );

    GXV_TRACE(( "interpret coverage 0x%04x by Apple style\n", coverage ));

    if ( KERN_IS_NEW( gxvalid ) )
    {
      if ( gxv_kern_coverage_new_apple_validate( coverage,
                                                 format,
                                                 gxvalid ) )
      {
        result = KERN_DIALECT_APPLE;
        goto Exit;
      }
    }

    if ( KERN_IS_CLASSIC( gxvalid ) && KERN_ALLOWS_APPLE( gxvalid ) )
    {
      if ( gxv_kern_coverage_classic_apple_validate( coverage,
                                                     format,
                                                     gxvalid ) )
      {
        result = KERN_DIALECT_APPLE;
        goto Exit;
      }
    }

    if ( KERN_IS_CLASSIC( gxvalid ) && KERN_ALLOWS_MS( gxvalid ) )
    {
      if ( gxv_kern_coverage_classic_microsoft_validate( coverage,
                                                         format,
                                                         gxvalid ) )
      {
        result = KERN_DIALECT_MS;
        goto Exit;
      }
    }

    GXV_TRACE(( "cannot interpret coverage, broken kern subtable\n" ));

  Exit:
    GXV_EXIT;
    return result;
  }