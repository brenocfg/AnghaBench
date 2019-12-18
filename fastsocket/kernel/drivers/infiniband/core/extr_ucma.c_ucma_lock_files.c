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
struct ucma_file {int /*<<< orphan*/  mut; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ucma_lock_files(struct ucma_file *file1, struct ucma_file *file2)
{
	/* Acquire mutex's based on pointer comparison to prevent deadlock. */
	if (file1 < file2) {
		mutex_lock(&file1->mut);
		mutex_lock(&file2->mut);
	} else {
		mutex_lock(&file2->mut);
		mutex_lock(&file1->mut);
	}
}