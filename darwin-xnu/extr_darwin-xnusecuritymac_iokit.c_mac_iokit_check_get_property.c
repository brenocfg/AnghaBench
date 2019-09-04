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
typedef  int /*<<< orphan*/  kauth_cred_t ;
typedef  int /*<<< orphan*/  io_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  iokit_check_get_property ; 

int
mac_iokit_check_get_property(kauth_cred_t cred, io_object_t registry_entry, const char *name)
{
	int error;

	MAC_CHECK(iokit_check_get_property, cred, registry_entry, name);
	return (error);
}