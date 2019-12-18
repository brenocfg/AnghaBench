#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kref {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  class; } ;

/* Variables and functions */
 int /*<<< orphan*/  class_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* uio_class ; 
 int /*<<< orphan*/  uio_major_cleanup () ; 

__attribute__((used)) static void release_uio_class(struct kref *kref)
{
	/* Ok, we cheat as we know we only have one uio_class */
	class_destroy(uio_class->class);
	kfree(uio_class);
	uio_major_cleanup();
	uio_class = NULL;
}