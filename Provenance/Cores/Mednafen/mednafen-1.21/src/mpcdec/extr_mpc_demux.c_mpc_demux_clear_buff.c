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
struct TYPE_4__ {int count; int /*<<< orphan*/  buff; } ;
struct TYPE_5__ {scalar_t__ block_frames; scalar_t__ block_bits; TYPE_1__ bits_reader; int /*<<< orphan*/  buffer; scalar_t__ bytes_total; } ;
typedef  TYPE_2__ mpc_demux ;

/* Variables and functions */

__attribute__((used)) static void mpc_demux_clear_buff(mpc_demux * d)
{
	d->bytes_total = 0;
	d->bits_reader.buff = d->buffer;
	d->bits_reader.count = 8;
	d->block_bits = 0;
	d->block_frames = 0;
}