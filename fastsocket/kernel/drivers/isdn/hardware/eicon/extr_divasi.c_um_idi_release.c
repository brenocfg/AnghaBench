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
struct inode {int dummy; } ;
struct file {int /*<<< orphan*/  private_data; } ;
struct TYPE_2__ {unsigned int adapter_nr; } ;
typedef  TYPE_1__ diva_um_idi_os_context_t ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ diva_um_id_get_os_context (int /*<<< orphan*/ ) ; 
 scalar_t__ divas_um_idi_delete_entity (int,int /*<<< orphan*/ ) ; 
 int remove_entity (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int um_idi_release(struct inode *inode, struct file *file)
{
	diva_um_idi_os_context_t *p_os;
	unsigned int adapter_nr;
	int ret = 0;

	if (!(file->private_data)) {
		ret = -ENODEV;
		goto out;
	}

	if (!(p_os =
		(diva_um_idi_os_context_t *) diva_um_id_get_os_context(file->private_data))) {
		ret = -ENODEV;
		goto out;
	}

	adapter_nr = p_os->adapter_nr;

	if ((ret = remove_entity(file->private_data))) {
		goto out;
	}

	if (divas_um_idi_delete_entity
	    ((int) adapter_nr, file->private_data)) {
		ret = -ENODEV;
		goto out;
	}

      out:
	return (ret);
}