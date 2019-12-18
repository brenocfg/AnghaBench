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
struct TYPE_3__ {int /*<<< orphan*/  ps_sh; } ;
typedef  int /*<<< orphan*/  PE_SecHdr ;
typedef  TYPE_1__ PE_Scn ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  errno ; 

PE_SecHdr *
pe_section_header(PE_Scn *ps)
{

	if (ps == NULL) {
		errno = EINVAL;
		return (NULL);
	}

	return (&ps->ps_sh);
}