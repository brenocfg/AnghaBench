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
struct vm_area_struct {int /*<<< orphan*/  vm_start; int /*<<< orphan*/  vm_mm; struct vm_area_struct* vm_next; } ;
struct anon_vma {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct vm_area_struct* find_vma_prev (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_area_struct**) ; 
 struct anon_vma* reusable_anon_vma (struct vm_area_struct*,struct vm_area_struct*,struct vm_area_struct*) ; 

struct anon_vma *find_mergeable_anon_vma(struct vm_area_struct *vma)
{
	struct anon_vma *anon_vma;
	struct vm_area_struct *near;

	near = vma->vm_next;
	if (!near)
		goto try_prev;

	anon_vma = reusable_anon_vma(near, vma, near);
	if (anon_vma)
		return anon_vma;
try_prev:
	/*
	 * It is potentially slow to have to call find_vma_prev here.
	 * But it's only on the first write fault on the vma, not
	 * every time, and we could devise a way to avoid it later
	 * (e.g. stash info in next's anon_vma_node when assigning
	 * an anon_vma, or when trying vma_merge).  Another time.
	 */
	BUG_ON(find_vma_prev(vma->vm_mm, vma->vm_start, &near) != vma);
	if (!near)
		goto none;

	anon_vma = reusable_anon_vma(near, near, vma);
	if (anon_vma)
		return anon_vma;
none:
	/*
	 * There's no absolute need to look only at touching neighbours:
	 * we could search further afield for "compatible" anon_vmas.
	 * But it would probably just be a waste of time searching,
	 * or lead to too many vmas hanging off the same anon_vma.
	 * We're trying to allow mprotect remerging later on,
	 * not trying to minimize memory used for anon_vmas.
	 */
	return NULL;
}