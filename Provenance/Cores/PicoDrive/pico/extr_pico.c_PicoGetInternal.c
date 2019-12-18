#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int pint_t ;
struct TYPE_8__ {int vint; int /*<<< orphan*/  vptr; } ;
typedef  TYPE_3__ pint_ret_t ;
struct TYPE_7__ {int* reg; } ;
struct TYPE_6__ {int pal; } ;
struct TYPE_9__ {TYPE_2__ video; TYPE_1__ m; int /*<<< orphan*/  rom; } ;

/* Variables and functions */
#define  PI_IS240_LINES 131 
#define  PI_IS40_CELL 130 
#define  PI_ISPAL 129 
#define  PI_ROM 128 
 TYPE_5__ Pico ; 

void PicoGetInternal(pint_t which, pint_ret_t *r)
{
  switch (which)
  {
    case PI_ROM:         r->vptr = Pico.rom; break;
    case PI_ISPAL:       r->vint = Pico.m.pal; break;
    case PI_IS40_CELL:   r->vint = Pico.video.reg[12]&1; break;
    case PI_IS240_LINES: r->vint = Pico.m.pal && (Pico.video.reg[1]&8); break;
  }
}