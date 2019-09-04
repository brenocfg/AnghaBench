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
typedef  int /*<<< orphan*/  uint64_t ;
struct ucred {int dummy; } ;
struct fileglob {int /*<<< orphan*/  fg_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_CHECK (int /*<<< orphan*/ ,struct ucred*,struct fileglob*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  file_check_mmap ; 
 int /*<<< orphan*/  panic (char*) ; 

int
mac_file_check_mmap(struct ucred *cred, struct fileglob *fg, int prot,
    int flags, uint64_t offset, int *maxprot)
{
	int error;
	int maxp;

	maxp = *maxprot;
	MAC_CHECK(file_check_mmap, cred, fg, fg->fg_label, prot, flags, offset, &maxp);
	if ((maxp | *maxprot) != *maxprot)
		panic("file_check_mmap increased max protections");
	*maxprot = maxp;
	return (error);
}