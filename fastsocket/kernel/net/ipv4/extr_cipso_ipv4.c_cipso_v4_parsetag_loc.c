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
struct netlbl_lsm_secattr {int /*<<< orphan*/  flags; TYPE_1__ attr; } ;
struct cipso_v4_doi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETLBL_SECATTR_SECID ; 

__attribute__((used)) static int cipso_v4_parsetag_loc(const struct cipso_v4_doi *doi_def,
				 const unsigned char *tag,
				 struct netlbl_lsm_secattr *secattr)
{
	secattr->attr.secid = *(u32 *)&tag[2];
	secattr->flags |= NETLBL_SECATTR_SECID;

	return 0;
}