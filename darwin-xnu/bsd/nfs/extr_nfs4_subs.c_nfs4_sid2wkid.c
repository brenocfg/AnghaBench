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
struct TYPE_3__ {int sid_kind; int sid_authcount; int* sid_authority; int* sid_authorities; } ;
typedef  TYPE_1__ ntsid_t ;

/* Variables and functions */

__attribute__((used)) static const char*
nfs4_sid2wkid(ntsid_t *sp)
{
	if ((sp->sid_kind == 1) && (sp->sid_authcount == 1)) {
		/* check if it's one of our well-known ACE WHO names */
		if (sp->sid_authority[5] == 0) {
			if (sp->sid_authorities[0] == 0) // S-1-0-0
				return ("nobody@localdomain");
		} else if (sp->sid_authority[5] == 1) {
			if (sp->sid_authorities[0] == 0) // S-1-1-0
				return ("EVERYONE@");
		} else if (sp->sid_authority[5] == 3) {
			if (sp->sid_authorities[0] == 0) // S-1-3-0
				return ("OWNER@");
			else if (sp->sid_authorities[0] == 1) // S-1-3-1
				return ("GROUP@");
		} else if (sp->sid_authority[5] == 5) {
			if (sp->sid_authorities[0] == 1) // S-1-5-1
				return ("DIALUP@");
			else if (sp->sid_authorities[0] == 2) // S-1-5-2
				return ("NETWORK@");
			else if (sp->sid_authorities[0] == 3) // S-1-5-3
				return ("BATCH@");
			else if (sp->sid_authorities[0] == 4) // S-1-5-4
				return ("INTERACTIVE@");
			else if (sp->sid_authorities[0] == 6) // S-1-5-6
				return ("SERVICE@");
			else if (sp->sid_authorities[0] == 7) // S-1-5-7
				return ("ANONYMOUS@");
			else if (sp->sid_authorities[0] == 11) // S-1-5-11
				return ("AUTHENTICATED@");
		}
	}
	return (NULL);
}