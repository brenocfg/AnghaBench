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
struct osd_dev {struct file* file; } ;
struct osd_uld_device {struct osd_dev od; } ;
struct file {struct osd_uld_device* private_data; int /*<<< orphan*/ * f_op; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct osd_dev* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct file*) ; 
 int /*<<< orphan*/  OSD_ERR (char*) ; 
 int /*<<< orphan*/  O_RDWR ; 
 int PTR_ERR (struct file*) ; 
 struct file* filp_open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int /*<<< orphan*/  kfree (struct osd_dev*) ; 
 struct osd_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osd_fops ; 

struct osd_dev *osduld_path_lookup(const char *name)
{
	struct osd_uld_device *oud;
	struct osd_dev *od;
	struct file *file;
	int error;

	if (!name || !*name) {
		OSD_ERR("Mount with !path || !*path\n");
		return ERR_PTR(-EINVAL);
	}

	od = kzalloc(sizeof(*od), GFP_KERNEL);
	if (!od)
		return ERR_PTR(-ENOMEM);

	file = filp_open(name, O_RDWR, 0);
	if (IS_ERR(file)) {
		error = PTR_ERR(file);
		goto free_od;
	}

	if (file->f_op != &osd_fops){
		error = -EINVAL;
		goto close_file;
	}

	oud = file->private_data;

	*od = oud->od;
	od->file = file;

	return od;

close_file:
	fput(file);
free_od:
	kfree(od);
	return ERR_PTR(error);
}