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
struct psmouse {struct fsp_data* private; } ;
struct fsp_data {int /*<<< orphan*/  flags; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  FSPDRV_FLAG_EN_OPC ; 

__attribute__((used)) static ssize_t fsp_attr_set_flags(struct psmouse *psmouse, void *data,
					const char *buf, size_t count)
{
	struct fsp_data *pad = psmouse->private;
	size_t i;

	for (i = 0; i < count; i++) {
		switch (buf[i]) {
		case 'C':
			pad->flags |= FSPDRV_FLAG_EN_OPC;
			break;
		case 'c':
			pad->flags &= ~FSPDRV_FLAG_EN_OPC;
			break;
		default:
			return -EINVAL;
		}
	}
	return count;
}