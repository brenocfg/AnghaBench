#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int width; int frame_size; int /*<<< orphan*/ ** frame; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ PAFVideoDecContext ;

/* Variables and functions */
 int bytestream2_get_be16 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void set_src_position(PAFVideoDecContext *c,
                             const uint8_t **p,
                             const uint8_t **pend)
{
    int val  = bytestream2_get_be16(&c->gb);
    int page = val >> 14;
    int x    = (val & 0x7F);
    int y    = ((val >> 7) & 0x7F);

    *p    = c->frame[page] + x * 2 + y * 2 * c->width;
    *pend = c->frame[page] + c->frame_size;
}