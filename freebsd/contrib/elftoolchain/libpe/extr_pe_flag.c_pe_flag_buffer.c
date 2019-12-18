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
struct TYPE_2__ {unsigned int sb_flags; } ;
typedef  TYPE_1__ PE_SecBuf ;
typedef  scalar_t__ PE_Cmd ;
typedef  int /*<<< orphan*/  PE_Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ PE_C_CLR ; 
 scalar_t__ PE_C_SET ; 
 unsigned int PE_F_DIRTY ; 
 int /*<<< orphan*/  errno ; 

int
pe_flag_buffer(PE_Buffer *pb, PE_Cmd c, unsigned int flags)
{
	PE_SecBuf *sb;

	if (pb == NULL || (c != PE_C_SET && c != PE_C_CLR) ||
	    (flags & ~PE_F_DIRTY) != 0) {
		errno = EINVAL;
		return (-1);
	}

	sb = (PE_SecBuf *) pb;

	if (c == PE_C_SET)
		sb->sb_flags |= flags;
	else
		sb->sb_flags &= ~flags;

	return (0);
}