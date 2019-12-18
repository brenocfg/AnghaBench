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
typedef  scalar_t__ u16 ;
struct vio_error_entry {scalar_t__ rc; } ;

/* Variables and functions */
 struct vio_error_entry* vio_default_errors ; 
 struct vio_error_entry const vio_no_error ; 
 struct vio_error_entry const vio_unknown_error ; 

const struct vio_error_entry *vio_lookup_rc(
		const struct vio_error_entry *local_table, u16 rc)
{
	const struct vio_error_entry *cur;

	if (!rc)
		return &vio_no_error;
	if (local_table)
		for (cur = local_table; cur->rc; ++cur)
			if (cur->rc == rc)
				return cur;
	for (cur = vio_default_errors; cur->rc; ++cur)
		if (cur->rc == rc)
			return cur;
	return &vio_unknown_error;
}