#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* priv_data; } ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int /*<<< orphan*/  display; int /*<<< orphan*/  dither; int /*<<< orphan*/  window_height; int /*<<< orphan*/  window_width; int /*<<< orphan*/  canvas; } ;
typedef  TYPE_1__ CACAContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  caca_dither_bitmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  caca_refresh_display (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int caca_write_packet(AVFormatContext *s, AVPacket *pkt)
{
    CACAContext *c = s->priv_data;

    caca_dither_bitmap(c->canvas, 0, 0, c->window_width, c->window_height, c->dither, pkt->data);
    caca_refresh_display(c->display);

    return 0;
}