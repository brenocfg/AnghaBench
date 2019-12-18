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
struct TYPE_5__ {int /*<<< orphan*/  bit_left; } ;
struct TYPE_4__ {int range; TYPE_2__ pb; scalar_t__ outstanding_count; scalar_t__ low; } ;
typedef  TYPE_1__ CABACContext ;

/* Variables and functions */
 int /*<<< orphan*/  init_put_bits (TYPE_2__*,int /*<<< orphan*/ *,int) ; 

void ff_init_cabac_encoder(CABACContext *c, uint8_t *buf, int buf_size){
    init_put_bits(&c->pb, buf, buf_size);

    c->low= 0;
    c->range= 0x1FE;
    c->outstanding_count= 0;
    c->pb.bit_left++; //avoids firstBitFlag
}