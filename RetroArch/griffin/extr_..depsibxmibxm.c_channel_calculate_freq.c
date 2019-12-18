#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct channel {int period; int vibrato_add; int arpeggio_add; int freq; TYPE_2__* replay; } ;
struct TYPE_4__ {TYPE_1__* module; } ;
struct TYPE_3__ {int c2_rate; scalar_t__ linear_periods; } ;

/* Variables and functions */
 int FP_SHIFT ; 
 int exp_2 (int) ; 

__attribute__((used)) static void channel_calculate_freq( struct channel *channel ) {
	int per = channel->period + channel->vibrato_add;
	if( channel->replay->module->linear_periods ) {
		per = per - ( channel->arpeggio_add << 6 );
		if( per < 28 || per > 7680 ) {
			per = 7680;
		}
		channel->freq = ( ( channel->replay->module->c2_rate >> 4 )
			* exp_2( ( ( 4608 - per ) << FP_SHIFT ) / 768 ) ) >> ( FP_SHIFT - 4 );
	} else {
		if( per > 29021 ) {
			per = 29021;
		}
		per = ( per << FP_SHIFT ) / exp_2( ( channel->arpeggio_add << FP_SHIFT ) / 12 );
		if( per < 28 ) {
			per = 29021;
		}
		channel->freq = channel->replay->module->c2_rate * 1712 / per;
	}
}