#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  BV; int /*<<< orphan*/  lastNDV; } ;
struct TYPE_4__ {TYPE_1__ blend; int /*<<< orphan*/  memory; } ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  TYPE_2__* CF2_Font ;

/* Variables and functions */
 int /*<<< orphan*/  FT_FREE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
  cf2_free_instance( void*  ptr )
  {
    CF2_Font  font = (CF2_Font)ptr;


    if ( font )
    {
      FT_Memory  memory = font->memory;


      FT_FREE( font->blend.lastNDV );
      FT_FREE( font->blend.BV );
    }
  }