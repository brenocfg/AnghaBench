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

/* Variables and functions */
 unsigned long* a2i ; 
 unsigned char* ddigits ; 
 unsigned char* hdigits ; 
 scalar_t__ isdigok (unsigned char const*,char) ; 
 unsigned char* odigits ; 

__attribute__((used)) static unsigned long
  _bdf_atoul( char*   s,
              char**  end,
              int     base )
  {
    unsigned long         v;
    const unsigned char*  dmap;


    if ( s == 0 || *s == 0 )
      return 0;

    /* Make sure the radix is something recognizable.  Default to 10. */
    switch ( base )
    {
    case 8:
      dmap = odigits;
      break;
    case 16:
      dmap = hdigits;
      break;
    default:
      base = 10;
      dmap = ddigits;
      break;
    }

    /* Check for the special hex prefix. */
    if ( *s == '0'                                  &&
         ( *( s + 1 ) == 'x' || *( s + 1 ) == 'X' ) )
    {
      base = 16;
      dmap = hdigits;
      s   += 2;
    }

    for ( v = 0; isdigok( dmap, *s ); s++ )
      v = v * base + a2i[(int)*s];

    if ( end != 0 )
      *end = s;

    return v;
  }