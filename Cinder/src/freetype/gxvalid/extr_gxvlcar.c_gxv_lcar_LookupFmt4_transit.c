#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ u; } ;
struct TYPE_10__ {int /*<<< orphan*/  u; } ;
struct TYPE_9__ {TYPE_1__* root; } ;
struct TYPE_8__ {int base; int limit; } ;
typedef  TYPE_2__* GXV_Validator ;
typedef  TYPE_3__ GXV_LookupValueDesc ;
typedef  TYPE_4__* GXV_LookupValueCPtr ;
typedef  int FT_UShort ;
typedef  int FT_Bytes ;

/* Variables and functions */
 int /*<<< orphan*/  FT_NEXT_USHORT (int) ; 
 int /*<<< orphan*/  FT_UNUSED (int) ; 
 int /*<<< orphan*/  GXV_LIMIT_CHECK (int) ; 

__attribute__((used)) static GXV_LookupValueDesc
  gxv_lcar_LookupFmt4_transit( FT_UShort            relative_gindex,
                               GXV_LookupValueCPtr  base_value_p,
                               FT_Bytes             lookuptbl_limit,
                               GXV_Validator        gxvalid )
  {
    FT_Bytes             p;
    FT_Bytes             limit;
    FT_UShort            offset;
    GXV_LookupValueDesc  value;

    FT_UNUSED( lookuptbl_limit );

    /* XXX: check range? */
    offset = (FT_UShort)( base_value_p->u +
                          relative_gindex * sizeof ( FT_UShort ) );
    p      = gxvalid->root->base + offset;
    limit  = gxvalid->root->limit;

    GXV_LIMIT_CHECK ( 2 );
    value.u = FT_NEXT_USHORT( p );

    return value;
  }