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
struct port_chan {int /*<<< orphan*/  kernel_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct port_chan*) ; 
 int /*<<< orphan*/  port_kern_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void port_free(void *d)
{
	struct port_chan *data = d;

	port_kern_free(data->kernel_data);
	kfree(data);
}