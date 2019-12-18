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
struct TYPE_2__ {int /*<<< orphan*/  xpcm_buffer; int /*<<< orphan*/  xpcm_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PicoPicoPCMReset () ; 
 TYPE_1__ PicoPicohw ; 

__attribute__((used)) static void PicoResetPico(void)
{
  PicoPicoPCMReset();
  PicoPicohw.xpcm_ptr = PicoPicohw.xpcm_buffer;
}