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
struct TYPE_2__ {char* name; int /*<<< orphan*/  chksum; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ HD_USTAR ;

/* Variables and functions */
 int BLKMULT ; 
 int /*<<< orphan*/  OCT ; 
 int /*<<< orphan*/  TMAGIC ; 
 scalar_t__ TMAGLEN ; 
 scalar_t__ asc_ul (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ tar_chksm (char*,int) ; 

int
ustar_id(char *blk, int size)
{
	HD_USTAR *hd;

	if (size < BLKMULT)
		return(-1);
	hd = (HD_USTAR *)blk;

	/*
	 * check for block of zero's first, a simple and fast test then check
	 * ustar magic cookie. We should use TMAGLEN, but some USTAR archive
	 * programs are fouled up and create archives missing the \0. Last we
	 * check the checksum. If ok we have to assume it is a valid header.
	 */
	if (hd->name[0] == '\0')
		return(-1);
	if (strncmp(hd->magic, TMAGIC, TMAGLEN - 1) != 0)
		return(-1);
	if (asc_ul(hd->chksum,sizeof(hd->chksum),OCT) != tar_chksm(blk,BLKMULT))
		return(-1);
	return(0);
}