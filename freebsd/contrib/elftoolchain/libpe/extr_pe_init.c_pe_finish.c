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
typedef  int /*<<< orphan*/  PE ;

/* Variables and functions */
 int /*<<< orphan*/  libpe_release_object (int /*<<< orphan*/ *) ; 

void
pe_finish(PE *pe)
{

	if (pe == NULL)
		return;

	libpe_release_object(pe);
}