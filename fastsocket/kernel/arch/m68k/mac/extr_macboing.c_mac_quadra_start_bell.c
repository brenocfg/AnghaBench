#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mac_asc_wave_tab ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_3__ {scalar_t__ expires; int /*<<< orphan*/  function; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  local_irq_restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_save (int /*<<< orphan*/ ) ; 
 int* mac_asc_regs ; 
 unsigned int mac_asc_samplespersec ; 
 unsigned int mac_bell_duration ; 
 scalar_t__ mac_bell_phase ; 
 unsigned int mac_bell_phasepersample ; 
 int /*<<< orphan*/  mac_quadra_ring_bell ; 
 TYPE_1__ mac_sound_timer ; 

__attribute__((used)) static void mac_quadra_start_bell( unsigned int freq, unsigned int length, unsigned int volume )
{
	__u32 flags;

	/* if the bell is already ringing, ring longer */
	if ( mac_bell_duration > 0 )
	{
		mac_bell_duration += length;
		return;
	}

	mac_bell_duration = length;
	mac_bell_phase = 0;
	mac_bell_phasepersample = ( freq * sizeof( mac_asc_wave_tab ) ) / mac_asc_samplespersec;
	/* this is reasonably big for small frequencies */

	local_irq_save(flags);

	/* set the volume */
	mac_asc_regs[ 0x806 ] = volume;

	/* set up the ASC registers */
	if ( mac_asc_regs[ 0x801 ] != 1 )
	{
		/* select mono mode */
		mac_asc_regs[ 0x807 ] = 0;
		/* select sampled sound mode */
		mac_asc_regs[ 0x802 ] = 0;
		/* ??? */
		mac_asc_regs[ 0x801 ] = 1;
		mac_asc_regs[ 0x803 ] |= 0x80;
		mac_asc_regs[ 0x803 ] &= 0x7F;
	}

	mac_sound_timer.function = mac_quadra_ring_bell;
	mac_sound_timer.expires = jiffies + 1;
	add_timer( &mac_sound_timer );

	local_irq_restore(flags);
}