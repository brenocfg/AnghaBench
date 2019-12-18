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

/* Variables and functions */
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ class_create (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_count ; 
 scalar_t__ timed_output_class ; 

__attribute__((used)) static int create_timed_output_class(void)
{
	if (!timed_output_class) {
		timed_output_class = class_create(THIS_MODULE, "timed_output");
		if (IS_ERR(timed_output_class))
			return PTR_ERR(timed_output_class);
		atomic_set(&device_count, 0);
	}

	return 0;
}