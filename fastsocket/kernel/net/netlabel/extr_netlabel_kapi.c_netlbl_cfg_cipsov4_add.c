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
struct netlbl_audit {int dummy; } ;
struct cipso_v4_doi {int dummy; } ;

/* Variables and functions */
 int cipso_v4_doi_add (struct cipso_v4_doi*,struct netlbl_audit*) ; 

int netlbl_cfg_cipsov4_add(struct cipso_v4_doi *doi_def,
			   struct netlbl_audit *audit_info)
{
	return cipso_v4_doi_add(doi_def, audit_info);
}