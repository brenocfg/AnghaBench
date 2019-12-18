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
struct echoaudio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE_INIT (char*) ; 
 int /*<<< orphan*/  ECHOGAIN_MUTED ; 
 int num_busses_in (struct echoaudio*) ; 
 int num_busses_out (struct echoaudio*) ; 
 int num_pipes_out (struct echoaudio*) ; 
 int set_input_gain (struct echoaudio*,int,int /*<<< orphan*/ ) ; 
 int set_monitor_gain (struct echoaudio*,int,int,int /*<<< orphan*/ ) ; 
 int set_output_gain (struct echoaudio*,int,int /*<<< orphan*/ ) ; 
 int set_vmixer_gain (struct echoaudio*,int,int,int /*<<< orphan*/ ) ; 
 int update_input_line_level (struct echoaudio*) ; 
 int update_output_line_level (struct echoaudio*) ; 
 int update_vmixer_level (struct echoaudio*) ; 

__attribute__((used)) static int init_line_levels(struct echoaudio *chip)
{
	int st, i, o;

	DE_INIT(("init_line_levels\n"));

	/* Mute output busses */
	for (i = 0; i < num_busses_out(chip); i++)
		if ((st = set_output_gain(chip, i, ECHOGAIN_MUTED)))
			return st;
	if ((st = update_output_line_level(chip)))
		return st;

#ifdef ECHOCARD_HAS_VMIXER
	/* Mute the Vmixer */
	for (i = 0; i < num_pipes_out(chip); i++)
		for (o = 0; o < num_busses_out(chip); o++)
			if ((st = set_vmixer_gain(chip, o, i, ECHOGAIN_MUTED)))
				return st;
	if ((st = update_vmixer_level(chip)))
		return st;
#endif /* ECHOCARD_HAS_VMIXER */

#ifdef ECHOCARD_HAS_MONITOR
	/* Mute the monitor mixer */
	for (o = 0; o < num_busses_out(chip); o++)
		for (i = 0; i < num_busses_in(chip); i++)
			if ((st = set_monitor_gain(chip, o, i, ECHOGAIN_MUTED)))
				return st;
	if ((st = update_output_line_level(chip)))
		return st;
#endif /* ECHOCARD_HAS_MONITOR */

#ifdef ECHOCARD_HAS_INPUT_GAIN
	for (i = 0; i < num_busses_in(chip); i++)
		if ((st = set_input_gain(chip, i, ECHOGAIN_MUTED)))
			return st;
	if ((st = update_input_line_level(chip)))
		return st;
#endif /* ECHOCARD_HAS_INPUT_GAIN */

	return 0;
}