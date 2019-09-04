#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cs_blob {TYPE_1__* csb_cd; } ;
struct TYPE_2__ {scalar_t__ version; scalar_t__ teamOffset; } ;
typedef  TYPE_1__ CS_CodeDirectory ;

/* Variables and functions */
 scalar_t__ CS_SUPPORTSTEAMID ; 
 int cs_debug ; 
 int ntohl (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 

__attribute__((used)) static const char *
csblob_parse_teamid(struct cs_blob *csblob)
{
	const CS_CodeDirectory *cd;

	cd = csblob->csb_cd;

	if (ntohl(cd->version) < CS_SUPPORTSTEAMID)
		return NULL;

	if (cd->teamOffset == 0)
		return NULL;

	const char *name = ((const char *)cd) + ntohl(cd->teamOffset);
	if (cs_debug > 1)
		printf("found team-id %s in cdblob\n", name);

	return name;
}