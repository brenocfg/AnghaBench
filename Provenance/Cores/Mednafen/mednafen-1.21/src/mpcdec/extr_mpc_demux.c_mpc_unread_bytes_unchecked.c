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
typedef  scalar_t__ mpc_int32_t ;
struct TYPE_4__ {int count; scalar_t__ buff; } ;
struct TYPE_5__ {TYPE_1__ bits_reader; scalar_t__ buffer; scalar_t__ bytes_total; } ;
typedef  TYPE_2__ mpc_demux ;

/* Variables and functions */

__attribute__((used)) static mpc_int32_t mpc_unread_bytes_unchecked(mpc_demux * d) {
	return d->bytes_total + d->buffer - d->bits_reader.buff - ((8 - d->bits_reader.count) >> 3);
}