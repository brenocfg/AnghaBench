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
struct TYPE_4__ {int rem; scalar_t__ buf; scalar_t__ rng_cur; scalar_t__ ext; scalar_t__ total_bits; int /*<<< orphan*/  range; scalar_t__ value; } ;
typedef  TYPE_1__ OpusRangeCoder ;

/* Variables and functions */
 scalar_t__ OPUS_MAX_PACKET_SIZE ; 
 scalar_t__ OPUS_RC_BITS ; 
 int /*<<< orphan*/  OPUS_RC_TOP ; 
 int /*<<< orphan*/  ff_opus_rc_dec_raw_init (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 

void ff_opus_rc_enc_init(OpusRangeCoder *rc)
{
    rc->value = 0;
    rc->range = OPUS_RC_TOP;
    rc->total_bits = OPUS_RC_BITS + 1;
    rc->rem = -1;
    rc->ext =  0;
    rc->rng_cur = rc->buf;
    ff_opus_rc_dec_raw_init(rc, rc->buf + OPUS_MAX_PACKET_SIZE + 8, 0);
}