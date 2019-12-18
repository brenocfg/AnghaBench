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
typedef  int u32 ;
struct e752x_error_info {int nsi_ferr; int nsi_nerr; } ;

/* Variables and functions */
 int NSI_ERR_MASK ; 
 int NSI_FATAL_MASK ; 
 int NSI_NON_FATAL_MASK ; 
 int /*<<< orphan*/  nsi_error (int,int,int*,int) ; 

__attribute__((used)) static void e752x_check_ns_interface(struct e752x_error_info *info,
				int *error_found, int handle_error)
{
	u32 stat32;

	stat32 = info->nsi_ferr;
	if (stat32 & NSI_ERR_MASK) { /* Error, so process */
		if (stat32 & NSI_FATAL_MASK)	/* check for fatal errors */
			nsi_error(1, stat32 & NSI_FATAL_MASK, error_found,
				  handle_error);
		if (stat32 & NSI_NON_FATAL_MASK) /* check for non-fatal ones */
			nsi_error(0, stat32 & NSI_NON_FATAL_MASK, error_found,
				  handle_error);
	}
	stat32 = info->nsi_nerr;
	if (stat32 & NSI_ERR_MASK) {
		if (stat32 & NSI_FATAL_MASK)
			nsi_error(1, stat32 & NSI_FATAL_MASK, error_found,
				  handle_error);
		if (stat32 & NSI_NON_FATAL_MASK)
			nsi_error(0, stat32 & NSI_NON_FATAL_MASK, error_found,
				  handle_error);
	}
}