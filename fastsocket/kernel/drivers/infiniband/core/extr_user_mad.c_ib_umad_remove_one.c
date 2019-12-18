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
struct ib_umad_device {int end_port; int start_port; int /*<<< orphan*/  ref; int /*<<< orphan*/ * port; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 struct ib_umad_device* ib_get_client_data (struct ib_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_umad_kill_port (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_umad_release_dev ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umad_client ; 

__attribute__((used)) static void ib_umad_remove_one(struct ib_device *device)
{
	struct ib_umad_device *umad_dev = ib_get_client_data(device, &umad_client);
	int i;

	if (!umad_dev)
		return;

	for (i = 0; i <= umad_dev->end_port - umad_dev->start_port; ++i)
		ib_umad_kill_port(&umad_dev->port[i]);

	kref_put(&umad_dev->ref, ib_umad_release_dev);
}