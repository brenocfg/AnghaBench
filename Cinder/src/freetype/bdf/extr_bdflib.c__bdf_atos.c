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
 int SHRT_MAX ; 
 scalar_t__* a2i ; 
 int /*<<< orphan*/  ddigits ; 
 scalar_t__ sbitset (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static short
  _bdf_atos( char*  s )
  {
    short  v, neg;


    if ( s == 0 || *s == 0 )
      return 0;

    /* Check for a minus. */
    neg = 0;
    if ( *s == '-' )
    {
      s++;
      neg = 1;
    }

    for ( v = 0; sbitset( ddigits, *s ); s++ )
    {
      if ( v < ( SHRT_MAX - 9 ) / 10 )
        v = (short)( v * 10 + a2i[(int)*s] );
      else
      {
        v = SHRT_MAX;
        break;
      }
    }

    return (short)( ( !neg ) ? v : -v );
  }