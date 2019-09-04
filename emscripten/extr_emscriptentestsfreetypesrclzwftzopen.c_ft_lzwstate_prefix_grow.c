#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int prefix_size; scalar_t__ prefix; int /*<<< orphan*/ * suffix; int /*<<< orphan*/  memory; } ;
typedef  int /*<<< orphan*/  FT_UShort ;
typedef  int FT_UInt ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  TYPE_1__* FT_LzwState ;
typedef  int /*<<< orphan*/  FT_Error ;
typedef  int /*<<< orphan*/  FT_Byte ;

/* Variables and functions */
 int /*<<< orphan*/  FT_MEM_MOVE (int /*<<< orphan*/ *,scalar_t__,int) ; 
 scalar_t__ FT_REALLOC_MULT (scalar_t__,int,int,int) ; 

__attribute__((used)) static int
  ft_lzwstate_prefix_grow( FT_LzwState  state )
  {
    FT_UInt    old_size = state->prefix_size;
    FT_UInt    new_size = old_size;
    FT_Memory  memory   = state->memory;
    FT_Error   error;


    if ( new_size == 0 )  /* first allocation -> 9 bits */
      new_size = 512;
    else
      new_size += new_size >> 2;  /* don't grow too fast */

    /*
     *  Note that the `suffix' array is located in the same memory block
     *  pointed to by `prefix'.
     *
     *  I know that sizeof(FT_Byte) == 1 by definition, but it is clearer
     *  to write it literally.
     *
     */
    if ( FT_REALLOC_MULT( state->prefix, old_size, new_size,
                          sizeof ( FT_UShort ) + sizeof ( FT_Byte ) ) )
      return -1;

    /* now adjust `suffix' and move the data accordingly */
    state->suffix = (FT_Byte*)( state->prefix + new_size );

    FT_MEM_MOVE( state->suffix,
                 state->prefix + old_size,
                 old_size * sizeof ( FT_Byte ) );

    state->prefix_size = new_size;
    return 0;
  }