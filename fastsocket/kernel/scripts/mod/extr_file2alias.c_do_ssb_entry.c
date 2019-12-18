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
struct ssb_device_id {scalar_t__ vendor; scalar_t__ coreid; scalar_t__ revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD (char*,char*,int,scalar_t__) ; 
 scalar_t__ SSB_ANY_ID ; 
 scalar_t__ SSB_ANY_REV ; 
 scalar_t__ SSB_ANY_VENDOR ; 
 void* TO_NATIVE (scalar_t__) ; 
 int /*<<< orphan*/  add_wildcard (char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static int do_ssb_entry(const char *filename,
			struct ssb_device_id *id, char *alias)
{
	id->vendor = TO_NATIVE(id->vendor);
	id->coreid = TO_NATIVE(id->coreid);
	id->revision = TO_NATIVE(id->revision);

	strcpy(alias, "ssb:");
	ADD(alias, "v", id->vendor != SSB_ANY_VENDOR, id->vendor);
	ADD(alias, "id", id->coreid != SSB_ANY_ID, id->coreid);
	ADD(alias, "rev", id->revision != SSB_ANY_REV, id->revision);
	add_wildcard(alias);
	return 1;
}