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
struct fsp_data {int flags; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int FSPDRV_FLAG_EN_OPC ; 
 int /*<<< orphan*/  sprintf (char*,char*,char) ; 

__attribute__((used)) static ssize_t fsp_attr_show_flags(struct psmouse *psmouse,
					void *data, char *buf)
{
	struct fsp_data *pad = psmouse->private;

	return sprintf(buf, "%c\n",
			pad->flags & FSPDRV_FLAG_EN_OPC ? 'C' : 'c');
}