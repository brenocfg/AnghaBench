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
struct cs_blob {int dummy; } ;
struct TYPE_2__ {scalar_t__ identOffset; } ;
typedef  TYPE_1__ CS_CodeDirectory ;

/* Variables and functions */
 int /*<<< orphan*/  CSMAGIC_CODEDIRECTORY ; 
 int /*<<< orphan*/  CSSLOT_CODEDIRECTORY ; 
 scalar_t__ csblob_find_blob (struct cs_blob*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ntohl (scalar_t__) ; 

const char *
csblob_get_identity(struct cs_blob *csblob)
{
	const CS_CodeDirectory *cd;

	cd = (const CS_CodeDirectory *)csblob_find_blob(csblob, CSSLOT_CODEDIRECTORY, CSMAGIC_CODEDIRECTORY);
	if (cd == NULL)
		return NULL;

	if (cd->identOffset == 0)
		return NULL;

	return ((const char *)cd) + ntohl(cd->identOffset);
}