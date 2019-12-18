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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/ * uint32 ;
struct TYPE_4__ {scalar_t__ mapPtr; scalar_t__ tracePtr; int /*<<< orphan*/ * bufferStart; int /*<<< orphan*/ * bufferOffset; int /*<<< orphan*/ * mapShift; int /*<<< orphan*/ * stampShift; int /*<<< orphan*/ * dotMask; int /*<<< orphan*/ * cyclesPerLine; int /*<<< orphan*/ * cycles; } ;
struct TYPE_3__ {int word_ram_2M; } ;

/* Variables and functions */
 TYPE_2__ gfx ; 
 int /*<<< orphan*/  save_param (int /*<<< orphan*/ **,int) ; 
 TYPE_1__ scd ; 

int gfx_context_save(uint8 *state)
{
  uint32 tmp32;
  int bufferptr = 0;

  save_param(&gfx.cycles, sizeof(gfx.cycles));
  save_param(&gfx.cyclesPerLine, sizeof(gfx.cyclesPerLine));
  save_param(&gfx.dotMask, sizeof(gfx.dotMask));
  save_param(&gfx.stampShift, sizeof(gfx.stampShift));
  save_param(&gfx.mapShift, sizeof(gfx.mapShift));
  save_param(&gfx.bufferOffset, sizeof(gfx.bufferOffset));
  save_param(&gfx.bufferStart, sizeof(gfx.bufferStart));

  tmp32 = (uint8 *)(gfx.tracePtr) - scd.word_ram_2M;
  save_param(&tmp32, 4);

  tmp32 = (uint8 *)(gfx.mapPtr) - scd.word_ram_2M;
  save_param(&tmp32, 4);

  return bufferptr;
}