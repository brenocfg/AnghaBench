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
struct segment_info {int segment_type; int /*<<< orphan*/  lh; int /*<<< orphan*/  segment_name; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SEGMENT_SHARED ; 
 int /*<<< orphan*/  dcssblk_devices_sem ; 
 struct segment_info* dcssblk_get_segment_by_name (char*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct segment_info*) ; 
 struct segment_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int segment_load (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  segment_warning (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dcssblk_load_segment(char *name, struct segment_info **seg_info)
{
	int rc;

	/* already loaded? */
	down_read(&dcssblk_devices_sem);
	*seg_info = dcssblk_get_segment_by_name(name);
	up_read(&dcssblk_devices_sem);
	if (*seg_info != NULL)
		return -EEXIST;

	/* get a struct segment_info */
	*seg_info = kzalloc(sizeof(struct segment_info), GFP_KERNEL);
	if (*seg_info == NULL)
		return -ENOMEM;

	strcpy((*seg_info)->segment_name, name);

	/* load the segment */
	rc = segment_load(name, SEGMENT_SHARED,
			&(*seg_info)->start, &(*seg_info)->end);
	if (rc < 0) {
		segment_warning(rc, (*seg_info)->segment_name);
		kfree(*seg_info);
	} else {
		INIT_LIST_HEAD(&(*seg_info)->lh);
		(*seg_info)->segment_type = rc;
	}
	return rc;
}