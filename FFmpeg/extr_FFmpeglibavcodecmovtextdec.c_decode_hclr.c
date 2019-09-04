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
struct TYPE_4__ {int /*<<< orphan*/  hlit_color; } ;
struct TYPE_5__ {TYPE_1__ c; int /*<<< orphan*/  box_flags; } ;
typedef  TYPE_2__ MovTextContext ;
typedef  int /*<<< orphan*/  AVPacket ;

/* Variables and functions */
 int /*<<< orphan*/  HCLR_BOX ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int decode_hclr(const uint8_t *tsmb, MovTextContext *m, AVPacket *avpkt)
{
    m->box_flags |= HCLR_BOX;
    memcpy(m->c.hlit_color, tsmb, 4);
    tsmb += 4;
    return 0;
}