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
struct vm_area_struct {struct qib_mmap_info* vm_private_data; } ;
struct qib_mmap_info {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_release_mmap_info ; 

__attribute__((used)) static void qib_vma_close(struct vm_area_struct *vma)
{
	struct qib_mmap_info *ip = vma->vm_private_data;

	kref_put(&ip->ref, qib_release_mmap_info);
}