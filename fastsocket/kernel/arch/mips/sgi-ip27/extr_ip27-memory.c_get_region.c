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
typedef  int hubreg_t ;
typedef  int /*<<< orphan*/  cnodeid_t ;

/* Variables and functions */
 int COMPACT_TO_NASID_NODEID (int /*<<< orphan*/ ) ; 
 int NASID_TO_COARSEREG_SHFT ; 
 int NASID_TO_FINEREG_SHFT ; 
 scalar_t__ fine_mode ; 

__attribute__((used)) static hubreg_t get_region(cnodeid_t cnode)
{
	if (fine_mode)
		return COMPACT_TO_NASID_NODEID(cnode) >> NASID_TO_FINEREG_SHFT;
	else
		return COMPACT_TO_NASID_NODEID(cnode) >> NASID_TO_COARSEREG_SHFT;
}