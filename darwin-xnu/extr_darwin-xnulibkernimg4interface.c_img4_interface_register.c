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
typedef  int /*<<< orphan*/  img4_interface_t ;

/* Variables and functions */
 int /*<<< orphan*/  const* img4if ; 
 int /*<<< orphan*/  panic (char*) ; 

void
img4_interface_register(const img4_interface_t *i4)
{
	if (img4if) {
		panic("img4 interface already set");
	}
	img4if = i4;
}