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
struct knote {unsigned int kn_id; scalar_t__ kn_data; } ;

/* Variables and functions */
 long NOTE_EXIT ; 
 long NOTE_SIGNAL ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
filt_signal(struct knote *kn, long hint)
{

	if (hint & NOTE_SIGNAL) {
		hint &= ~NOTE_SIGNAL;

		if (kn->kn_id == (unsigned int)hint)
			kn->kn_data++;
	} else if (hint & NOTE_EXIT) {
		panic("filt_signal: detected NOTE_EXIT event");
	}

	return (kn->kn_data != 0);
}