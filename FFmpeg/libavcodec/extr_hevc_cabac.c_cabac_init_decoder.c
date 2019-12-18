#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ buffer; } ;
struct TYPE_10__ {TYPE_1__* HEVClc; } ;
struct TYPE_9__ {int /*<<< orphan*/  cc; TYPE_3__ gb; } ;
typedef  TYPE_2__ HEVCContext ;
typedef  TYPE_3__ GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  align_get_bits (TYPE_3__*) ; 
 int ff_init_cabac_decoder (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int get_bits_count (TYPE_3__*) ; 
 int get_bits_left (TYPE_3__*) ; 
 int /*<<< orphan*/  skip_bits (TYPE_3__*,int) ; 

__attribute__((used)) static int cabac_init_decoder(HEVCContext *s)
{
    GetBitContext *gb = &s->HEVClc->gb;
    skip_bits(gb, 1);
    align_get_bits(gb);
    return ff_init_cabac_decoder(&s->HEVClc->cc,
                          gb->buffer + get_bits_count(gb) / 8,
                          (get_bits_left(gb) + 7) / 8);
}