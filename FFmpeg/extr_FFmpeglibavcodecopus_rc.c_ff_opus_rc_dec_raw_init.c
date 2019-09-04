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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {scalar_t__ cacheval; scalar_t__ cachelen; int /*<<< orphan*/  bytes; int /*<<< orphan*/  const* position; } ;
struct TYPE_5__ {TYPE_1__ rb; } ;
typedef  TYPE_2__ OpusRangeCoder ;

/* Variables and functions */

void ff_opus_rc_dec_raw_init(OpusRangeCoder *rc, const uint8_t *rightend, uint32_t bytes)
{
    rc->rb.position = rightend;
    rc->rb.bytes    = bytes;
    rc->rb.cachelen = 0;
    rc->rb.cacheval = 0;
}