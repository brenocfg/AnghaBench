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
struct smb_hdr {int WordCount; } ;

/* Variables and functions */
 unsigned int get_bcc (struct smb_hdr*) ; 

unsigned int
smbCalcSize(struct smb_hdr *ptr)
{
	return (sizeof(struct smb_hdr) + (2 * ptr->WordCount) +
		2 /* size of the bcc field */ + get_bcc(ptr));
}