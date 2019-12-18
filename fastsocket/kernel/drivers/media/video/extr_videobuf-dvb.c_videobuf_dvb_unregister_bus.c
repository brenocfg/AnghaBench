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
struct videobuf_dvb_frontends {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  dvb_unregister_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  videobuf_dvb_dealloc_frontends (struct videobuf_dvb_frontends*) ; 

void videobuf_dvb_unregister_bus(struct videobuf_dvb_frontends *f)
{
	videobuf_dvb_dealloc_frontends(f);

	dvb_unregister_adapter(&f->adapter);
}