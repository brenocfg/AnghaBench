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
struct ports_device {int /*<<< orphan*/  c_ivq; } ;
struct port_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_buf (struct port_buffer*) ; 
 int /*<<< orphan*/  use_multiport (struct ports_device*) ; 
 struct port_buffer* virtqueue_detach_unused_buf (int /*<<< orphan*/ ) ; 
 struct port_buffer* virtqueue_get_buf (int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static void remove_controlq_data(struct ports_device *portdev)
{
	struct port_buffer *buf;
	unsigned int len;

	if (!use_multiport(portdev))
		return;

	while ((buf = virtqueue_get_buf(portdev->c_ivq, &len)))
		free_buf(buf);

	while ((buf = virtqueue_detach_unused_buf(portdev->c_ivq)))
		free_buf(buf);
}