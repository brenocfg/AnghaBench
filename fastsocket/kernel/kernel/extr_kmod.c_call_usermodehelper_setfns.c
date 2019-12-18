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
struct subprocess_info {void (* cleanup ) (struct subprocess_info*) ;int (* init ) (struct subprocess_info*) ;void* data; } ;

/* Variables and functions */

void call_usermodehelper_setfns(struct subprocess_info *info,
		    int (*init)(struct subprocess_info *info),
		    void (*cleanup)(struct subprocess_info *info),
		    void *data)
{
	info->cleanup = cleanup;
	info->init = init;
	info->data = data;
}