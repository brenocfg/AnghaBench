#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ num_bits; int* bytes; } ;
typedef  TYPE_1__* PS_Mask ;
typedef  scalar_t__ FT_UInt ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  int FT_Int ;
typedef  scalar_t__ FT_Error ;
typedef  int FT_Byte ;

/* Variables and functions */
 scalar_t__ PSH_Err_Ok ; 
 scalar_t__ ps_mask_ensure (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static FT_Error
  ps_mask_set_bit( PS_Mask    mask,
                   FT_Int     idx,
                   FT_Memory  memory )
  {
    FT_Error  error = PSH_Err_Ok;
    FT_Byte*  p;


    if ( idx < 0 )
      goto Exit;

    if ( (FT_UInt)idx >= mask->num_bits )
    {
      error = ps_mask_ensure( mask, idx + 1, memory );
      if ( error )
        goto Exit;

      mask->num_bits = idx + 1;
    }

    p    = mask->bytes + ( idx >> 3 );
    p[0] = (FT_Byte)( p[0] | ( 0x80 >> ( idx & 7 ) ) );

  Exit:
    return error;
  }