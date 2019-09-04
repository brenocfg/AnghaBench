#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int range; int low; int /*<<< orphan*/  pb; } ;
typedef  TYPE_1__ CABACContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  flush_put_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int put_bits_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_cabac_bit (TYPE_1__*,int) ; 
 int /*<<< orphan*/  renorm_cabac_encoder (TYPE_1__*) ; 

__attribute__((used)) static int put_cabac_terminate(CABACContext *c, int bit){
    c->range -= 2;

    if(!bit){
        renorm_cabac_encoder(c);
    }else{
        c->low += c->range;
        c->range= 2;

        renorm_cabac_encoder(c);

        av_assert0(c->low <= 0x1FF);
        put_cabac_bit(c, c->low>>9);
        put_bits(&c->pb, 2, ((c->low>>7)&3)|1);

        flush_put_bits(&c->pb); //FIXME FIXME FIXME XXX wrong
    }

    return (put_bits_count(&c->pb)+7)>>3;
}