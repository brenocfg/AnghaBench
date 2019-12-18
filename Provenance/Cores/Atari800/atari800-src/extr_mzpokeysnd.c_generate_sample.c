#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  PokeyState ;

/* Variables and functions */
 int POKEYSND_playback_freq ; 
 int /*<<< orphan*/  advance_ticks (int /*<<< orphan*/ *,int) ; 
 int pokey_frq ; 
 double read_resam_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static double generate_sample(PokeyState* ps)
{
    /*unsigned long ta = (subticks+pokey_frq)/POKEYSND_playback_freq;
    subticks = (subticks+pokey_frq)%POKEYSND_playback_freq;*/

    advance_ticks(ps, pokey_frq/POKEYSND_playback_freq);
    return read_resam_all(ps);
}