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
typedef  void* FT_ULong ;
typedef  int FT_UInt ;
typedef  int /*<<< orphan*/  FT_Byte ;
typedef  scalar_t__ FT_Bool ;

/* Variables and functions */
 scalar_t__ FT_BOOL (int) ; 
 void* PFR_NEXT_BYTE (int /*<<< orphan*/ *) ; 
 void* PFR_NEXT_ULONG (int /*<<< orphan*/ *) ; 
 void* PFR_NEXT_USHORT (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
  pfr_lookup_bitmap_data( FT_Byte*   base,
                          FT_Byte*   limit,
                          FT_UInt    count,
                          FT_UInt    flags,
                          FT_UInt    char_code,
                          FT_ULong*  found_offset,
                          FT_ULong*  found_size )
  {
    FT_UInt   left, right, char_len;
    FT_Bool   two = FT_BOOL( flags & 1 );
    FT_Byte*  buff;


    char_len = 4;
    if ( two )       char_len += 1;
    if ( flags & 2 ) char_len += 1;
    if ( flags & 4 ) char_len += 1;

    left  = 0;
    right = count;

    while ( left < right )
    {
      FT_UInt  middle, code;


      middle = ( left + right ) >> 1;
      buff   = base + middle * char_len;

      /* check that we are not outside of the table -- */
      /* this is possible with broken fonts...         */
      if ( buff + char_len > limit )
        goto Fail;

      if ( two )
        code = PFR_NEXT_USHORT( buff );
      else
        code = PFR_NEXT_BYTE( buff );

      if ( code == char_code )
        goto Found_It;

      if ( code < char_code )
        left = middle;
      else
        right = middle;
    }

  Fail:
    /* Not found */
    *found_size   = 0;
    *found_offset = 0;
    return;

  Found_It:
    if ( flags & 2 )
      *found_size = PFR_NEXT_USHORT( buff );
    else
      *found_size = PFR_NEXT_BYTE( buff );

    if ( flags & 4 )
      *found_offset = PFR_NEXT_ULONG( buff );
    else
      *found_offset = PFR_NEXT_USHORT( buff );
  }