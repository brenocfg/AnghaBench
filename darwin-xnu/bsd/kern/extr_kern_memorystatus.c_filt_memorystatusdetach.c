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
struct knote {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memorystatus_knote_unregister (struct knote*) ; 

__attribute__((used)) static void
filt_memorystatusdetach(struct knote *kn)
{
	memorystatus_knote_unregister(kn);
}