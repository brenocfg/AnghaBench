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

/* Variables and functions */
 int LLC_DEST_CONN ; 
 int LLC_DEST_SAP ; 
 int /*<<< orphan*/ ** llc_type_handlers ; 

void llc_remove_pack(int type)
{
	if (type == LLC_DEST_SAP || type == LLC_DEST_CONN)
		llc_type_handlers[type - 1] = NULL;
}