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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  secid; } ;
struct netlbl_lsm_secattr {int flags; TYPE_1__ attr; } ;
struct cipso_v4_doi {int dummy; } ;

/* Variables and functions */
 unsigned char CIPSO_V4_TAG_LOCAL ; 
 int CIPSO_V4_TAG_LOC_BLEN ; 
 int EPERM ; 
 int NETLBL_SECATTR_SECID ; 

__attribute__((used)) static int cipso_v4_gentag_loc(const struct cipso_v4_doi *doi_def,
			       const struct netlbl_lsm_secattr *secattr,
			       unsigned char *buffer,
			       u32 buffer_len)
{
	if (!(secattr->flags & NETLBL_SECATTR_SECID))
		return -EPERM;

	buffer[0] = CIPSO_V4_TAG_LOCAL;
	buffer[1] = CIPSO_V4_TAG_LOC_BLEN;
	*(u32 *)&buffer[2] = secattr->attr.secid;

	return CIPSO_V4_TAG_LOC_BLEN;
}