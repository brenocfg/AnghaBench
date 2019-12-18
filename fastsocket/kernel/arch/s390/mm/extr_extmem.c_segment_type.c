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
struct dcss_segment {int vm_segtype; int /*<<< orphan*/  dcss_name; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  MACHINE_IS_VM ; 
 int /*<<< orphan*/  dcss_mkname (char*,int /*<<< orphan*/ ) ; 
 int query_segment_type (struct dcss_segment*) ; 

int
segment_type (char* name)
{
	int rc;
	struct dcss_segment seg;

	if (!MACHINE_IS_VM)
		return -ENOSYS;

	dcss_mkname(name, seg.dcss_name);
	rc = query_segment_type (&seg);
	if (rc < 0)
		return rc;
	return seg.vm_segtype;
}