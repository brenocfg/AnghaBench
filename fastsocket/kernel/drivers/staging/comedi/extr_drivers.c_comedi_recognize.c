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
struct comedi_driver {char** board_name; unsigned int num_names; int offset; } ;

/* Variables and functions */
 scalar_t__ strcmp (char const* const,char const*) ; 

void *comedi_recognize(struct comedi_driver *driv, const char *name)
{
	unsigned i;
	const char *const *name_ptr = driv->board_name;
	for (i = 0; i < driv->num_names; i++) {
		if (strcmp(*name_ptr, name) == 0)
			return (void *)name_ptr;
		name_ptr =
		    (const char *const *)((const char *)name_ptr +
					  driv->offset);
	}

	return NULL;
}