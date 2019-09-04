#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  s4; } ;
struct TYPE_6__ {TYPE_1__ ean; } ;
typedef  TYPE_2__ zbar_decoder_t ;

/* Variables and functions */
 char decode_e (unsigned int,int /*<<< orphan*/ ,int) ; 
 unsigned int get_width (TYPE_2__*,int) ; 

__attribute__((used)) static inline signed char aux_mid (zbar_decoder_t *dcode)
{
    unsigned e = get_width(dcode, 4) + get_width(dcode, 5);
    return(decode_e(e, dcode->ean.s4, 7));
}