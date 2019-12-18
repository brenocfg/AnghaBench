#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int sid_kind; int sid_authcount; int* sid_authority; int* sid_authorities; } ;
typedef  TYPE_1__ ntsid_t ;

/* Variables and functions */
 int EINVAL ; 
 size_t MAXIDNAMELEN ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 size_t strnlen (char const*,size_t) ; 

__attribute__((used)) static int
nfs4_wkid2sid(const char *id, ntsid_t *sp)
{
	size_t len = strnlen(id, MAXIDNAMELEN);

	if (len == MAXIDNAMELEN || id[len-1] != '@')
		return (EINVAL);

	bzero(sp, sizeof(ntsid_t));
	sp->sid_kind = 1;
	sp->sid_authcount = 1;
	if (!strcmp(id, "OWNER@")) {
		// S-1-3-0
		sp->sid_authority[5] = 3;
		sp->sid_authorities[0] = 0;
	} else if (!strcmp(id, "GROUP@")) {
		// S-1-3-1
		sp->sid_authority[5] = 3;
		sp->sid_authorities[0] = 1;
	} else if (!strcmp(id, "EVERYONE@")) {
		// S-1-1-0
		sp->sid_authority[5] = 1;
		sp->sid_authorities[0] = 0;
	} else if (!strcmp(id, "INTERACTIVE@")) {
		// S-1-5-4
		sp->sid_authority[5] = 5;
		sp->sid_authorities[0] = 4;
	} else if (!strcmp(id, "NETWORK@")) {
		// S-1-5-2
		sp->sid_authority[5] = 5;
		sp->sid_authorities[0] = 2;
	} else if (!strcmp(id, "DIALUP@")) {
		// S-1-5-1
		sp->sid_authority[5] = 5;
		sp->sid_authorities[0] = 1;
	} else if (!strcmp(id, "BATCH@")) {
		// S-1-5-3
		sp->sid_authority[5] = 5;
		sp->sid_authorities[0] = 3;
	} else if (!strcmp(id, "ANONYMOUS@")) {
		// S-1-5-7
		sp->sid_authority[5] = 5;
		sp->sid_authorities[0] = 7;
	} else if (!strcmp(id, "AUTHENTICATED@")) {
		// S-1-5-11
		sp->sid_authority[5] = 5;
		sp->sid_authorities[0] = 11;
	} else if (!strcmp(id, "SERVICE@")) {
		// S-1-5-6
		sp->sid_authority[5] = 5;
		sp->sid_authorities[0] = 6;
	} else {
		// S-1-0-0 "NOBODY"
		sp->sid_authority[5] = 0;
		sp->sid_authorities[0] = 0;
	}
	return (0);
}