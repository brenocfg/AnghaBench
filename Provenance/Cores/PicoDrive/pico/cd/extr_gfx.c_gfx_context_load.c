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
typedef  scalar_t__ uint32 ;
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_4__ {scalar_t__ word_ram2M; } ;
struct TYPE_3__ {scalar_t__ y_step; int /*<<< orphan*/ * mapPtr; int /*<<< orphan*/ * tracePtr; scalar_t__ bufferStart; scalar_t__ bufferOffset; scalar_t__ mapShift; scalar_t__ stampShift; scalar_t__ dotMask; } ;

/* Variables and functions */
 TYPE_2__* Pico_mcd ; 
 TYPE_1__ gfx ; 
 int /*<<< orphan*/  load_param (scalar_t__*,int) ; 

int gfx_context_load(const uint8 *state)
{
  uint32 tmp32;
  int bufferptr = 0;

  //load_param(&gfx.cycles, sizeof(gfx.cycles));
  //load_param(&gfx.cyclesPerLine, sizeof(gfx.cyclesPerLine));
  load_param(&gfx.dotMask, sizeof(gfx.dotMask));
  load_param(&gfx.stampShift, sizeof(gfx.stampShift));
  load_param(&gfx.mapShift, sizeof(gfx.mapShift));
  load_param(&gfx.bufferOffset, sizeof(gfx.bufferOffset));
  load_param(&gfx.bufferStart, sizeof(gfx.bufferStart));

  load_param(&tmp32, 4);
  gfx.tracePtr = (uint16 *)(Pico_mcd->word_ram2M + tmp32);

  load_param(&tmp32, 4);
  gfx.mapPtr = (uint16 *)(Pico_mcd->word_ram2M + tmp32);

  load_param(&gfx.y_step, sizeof(gfx.y_step));

  return bufferptr;
}