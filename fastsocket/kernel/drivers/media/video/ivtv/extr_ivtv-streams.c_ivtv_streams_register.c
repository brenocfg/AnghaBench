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
struct ivtv {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int IVTV_MAX_STREAMS ; 
 int ivtv_reg_dev (struct ivtv*,int) ; 
 int /*<<< orphan*/  ivtv_streams_cleanup (struct ivtv*,int) ; 

int ivtv_streams_register(struct ivtv *itv)
{
	int type;
	int err = 0;

	/* Register V4L2 devices */
	for (type = 0; type < IVTV_MAX_STREAMS; type++)
		err |= ivtv_reg_dev(itv, type);

	if (err == 0)
		return 0;

	/* One or more streams could not be initialized. Clean 'em all up. */
	ivtv_streams_cleanup(itv, 1);
	return -ENOMEM;
}