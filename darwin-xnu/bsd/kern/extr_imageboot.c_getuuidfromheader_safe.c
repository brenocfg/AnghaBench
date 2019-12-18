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
typedef  int /*<<< orphan*/  uuid_t ;
struct uuid_command {scalar_t__ cmd; int /*<<< orphan*/  cmdsize; int /*<<< orphan*/  const uuid; } ;
struct TYPE_2__ {scalar_t__ magic; size_t sizeofcmds; size_t ncmds; } ;
typedef  TYPE_1__ kernel_mach_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUTHPRNT (char*) ; 
 scalar_t__ LC_UUID ; 
 scalar_t__ MH_MAGIC_64 ; 
 scalar_t__ os_add_overflow (int /*<<< orphan*/ ,size_t,size_t*) ; 

__attribute__((used)) static const uuid_t *
getuuidfromheader_safe(const void *buf, size_t bufsz, size_t *uuidsz)
{
	const struct uuid_command *cmd = NULL;
	const kernel_mach_header_t *mh = buf;

	/* space for the header and at least one load command? */
	if (bufsz < sizeof(kernel_mach_header_t) + sizeof(struct uuid_command)) {
		AUTHPRNT("libkern image too small");
		return NULL;
	}

	/* validate the mach header */
	if (mh->magic != MH_MAGIC_64 || (mh->sizeofcmds > bufsz - sizeof(kernel_mach_header_t))) {
		AUTHPRNT("invalid MachO header");
		return NULL;
	}

	/* iterate the load commands */
	size_t offset = sizeof(kernel_mach_header_t);
	for (size_t i = 0; i < mh->ncmds; i++) {
		cmd = buf + offset;

		if (cmd->cmd == LC_UUID) {
			*uuidsz = sizeof(cmd->uuid);
			return &cmd->uuid;
		}

		if (os_add_overflow(cmd->cmdsize, offset, &offset) ||
				offset > bufsz - sizeof(struct uuid_command)) {
			return NULL;
		}
	}

	return NULL;
}