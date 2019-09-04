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
struct segment_command_64 {int /*<<< orphan*/  flags; int /*<<< orphan*/  nsects; int /*<<< orphan*/  initprot; int /*<<< orphan*/  maxprot; int /*<<< orphan*/  filesize; int /*<<< orphan*/  fileoff; int /*<<< orphan*/  vmsize; int /*<<< orphan*/  vmaddr; int /*<<< orphan*/  segname; int /*<<< orphan*/  cmdsize; int /*<<< orphan*/  cmd; } ;
struct segment_command {int /*<<< orphan*/  flags; int /*<<< orphan*/  nsects; int /*<<< orphan*/  initprot; int /*<<< orphan*/  maxprot; int /*<<< orphan*/  filesize; int /*<<< orphan*/  fileoff; int /*<<< orphan*/  vmsize; int /*<<< orphan*/  vmaddr; int /*<<< orphan*/  segname; int /*<<< orphan*/  cmdsize; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
widen_segment_command(const struct segment_command *scp32,
    struct segment_command_64 *scp)
{
	scp->cmd = scp32->cmd;
	scp->cmdsize = scp32->cmdsize;
	bcopy(scp32->segname, scp->segname, sizeof(scp->segname));
	scp->vmaddr = scp32->vmaddr;
	scp->vmsize = scp32->vmsize;
	scp->fileoff = scp32->fileoff;
	scp->filesize = scp32->filesize;
	scp->maxprot = scp32->maxprot;
	scp->initprot = scp32->initprot;
	scp->nsects = scp32->nsects;
	scp->flags = scp32->flags;
}