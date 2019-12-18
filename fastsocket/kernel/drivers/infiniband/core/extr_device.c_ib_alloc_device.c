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
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ib_device* kzalloc (size_t,int /*<<< orphan*/ ) ; 

struct ib_device *ib_alloc_device(size_t size)
{
	BUG_ON(size < sizeof (struct ib_device));

	return kzalloc(size, GFP_KERNEL);
}