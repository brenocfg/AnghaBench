#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {void* hlit_end; void* hlit_start; } ;
struct TYPE_5__ {TYPE_1__ h; int /*<<< orphan*/  box_flags; } ;
typedef  TYPE_2__ MovTextContext ;
typedef  int /*<<< orphan*/  AVPacket ;

/* Variables and functions */
 void* AV_RB16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  HLIT_BOX ; 

__attribute__((used)) static int decode_hlit(const uint8_t *tsmb, MovTextContext *m, AVPacket *avpkt)
{
    m->box_flags |= HLIT_BOX;
    m->h.hlit_start = AV_RB16(tsmb);
    tsmb += 2;
    m->h.hlit_end = AV_RB16(tsmb);
    tsmb += 2;
    return 0;
}