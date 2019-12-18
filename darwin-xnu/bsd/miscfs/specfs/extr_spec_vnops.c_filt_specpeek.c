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
struct knote {scalar_t__ kn_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  filt_spec_common (struct knote*,int) ; 
 int spec_knote_select_and_link (struct knote*) ; 

__attribute__((used)) static int
filt_specpeek(struct knote *kn)
{
	int selres = 0;

	selres = spec_knote_select_and_link(kn);
	filt_spec_common(kn, selres);

	return kn->kn_data != 0;
}