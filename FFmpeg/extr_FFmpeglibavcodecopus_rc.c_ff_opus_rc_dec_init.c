#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int range; int total_bits; int /*<<< orphan*/  gb; scalar_t__ value; } ;
typedef  TYPE_1__ OpusRangeCoder ;

/* Variables and functions */
 scalar_t__ get_bits (int /*<<< orphan*/ *,int) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  opus_rc_dec_normalize (TYPE_1__*) ; 

int ff_opus_rc_dec_init(OpusRangeCoder *rc, const uint8_t *data, int size)
{
    int ret = init_get_bits8(&rc->gb, data, size);
    if (ret < 0)
        return ret;

    rc->range = 128;
    rc->value = 127 - get_bits(&rc->gb, 7);
    rc->total_bits = 9;
    opus_rc_dec_normalize(rc);

    return 0;
}