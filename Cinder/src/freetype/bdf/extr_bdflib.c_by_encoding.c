#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ encoding; } ;
typedef  TYPE_1__ bdf_glyph_t ;

/* Variables and functions */

__attribute__((used)) static int
  by_encoding( const void*  a,
               const void*  b )
  {
    bdf_glyph_t  *c1, *c2;


    c1 = (bdf_glyph_t *)a;
    c2 = (bdf_glyph_t *)b;

    if ( c1->encoding < c2->encoding )
      return -1;

    if ( c1->encoding > c2->encoding )
      return 1;

    return 0;
  }