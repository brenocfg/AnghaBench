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
struct vm_area_struct {unsigned long vm_end; unsigned long vm_start; int vm_flags; scalar_t__ vm_truncate_count; long vm_pgoff; struct vm_area_struct* vm_next; struct anon_vma* anon_vma; struct file* vm_file; struct mm_struct* vm_mm; } ;
struct prio_tree_root {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  map_count; } ;
struct file {struct address_space* f_mapping; } ;
struct anon_vma {int dummy; } ;
struct address_space {int /*<<< orphan*/  i_mmap_lock; struct prio_tree_root i_mmap; } ;
typedef  long pgoff_t ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int VM_EXECUTABLE ; 
 int VM_NONLINEAR ; 
 int /*<<< orphan*/  __insert_vm_struct (struct mm_struct*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  __remove_shared_vm_struct (struct vm_area_struct*,struct file*,struct address_space*) ; 
 int /*<<< orphan*/  __vma_link_file (struct vm_area_struct*) ; 
 int /*<<< orphan*/  __vma_unlink (struct mm_struct*,struct vm_area_struct*,struct vm_area_struct*) ; 
 scalar_t__ anon_vma_clone (struct vm_area_struct*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  anon_vma_lock (struct anon_vma*) ; 
 int /*<<< orphan*/  anon_vma_merge (struct vm_area_struct*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  anon_vma_unlock (struct anon_vma*) ; 
 int /*<<< orphan*/  flush_dcache_mmap_lock (struct address_space*) ; 
 int /*<<< orphan*/  flush_dcache_mmap_unlock (struct address_space*) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct vm_area_struct*) ; 
 int /*<<< orphan*/  mpol_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  removed_exe_file_vma (struct mm_struct*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  validate_mm (struct mm_struct*) ; 
 int /*<<< orphan*/  vm_area_cachep ; 
 int /*<<< orphan*/  vma_adjust_trans_huge (struct vm_area_struct*,unsigned long,unsigned long,long) ; 
 int /*<<< orphan*/  vma_policy (struct vm_area_struct*) ; 
 int /*<<< orphan*/  vma_prio_tree_insert (struct vm_area_struct*,struct prio_tree_root*) ; 
 int /*<<< orphan*/  vma_prio_tree_remove (struct vm_area_struct*,struct prio_tree_root*) ; 

int vma_adjust(struct vm_area_struct *vma, unsigned long start,
	unsigned long end, pgoff_t pgoff, struct vm_area_struct *insert)
{
	struct mm_struct *mm = vma->vm_mm;
	struct vm_area_struct *next = vma->vm_next;
	struct vm_area_struct *importer = NULL;
	struct address_space *mapping = NULL;
	struct prio_tree_root *root = NULL;
	struct anon_vma *anon_vma = NULL;
	struct file *file = vma->vm_file;
	long adjust_next = 0;
	int remove_next = 0;

	if (next && !insert) {
		struct vm_area_struct *exporter = NULL;

		if (end >= next->vm_end) {
			/*
			 * vma expands, overlapping all the next, and
			 * perhaps the one after too (mprotect case 6).
			 */
again:			remove_next = 1 + (end > next->vm_end);
			end = next->vm_end;
			exporter = next;
			importer = vma;
		} else if (end > next->vm_start) {
			/*
			 * vma expands, overlapping part of the next:
			 * mprotect case 5 shifting the boundary up.
			 */
			adjust_next = (end - next->vm_start) >> PAGE_SHIFT;
			exporter = next;
			importer = vma;
		} else if (end < vma->vm_end) {
			/*
			 * vma shrinks, and !insert tells it's not
			 * split_vma inserting another: so it must be
			 * mprotect case 4 shifting the boundary down.
			 */
			adjust_next = - ((vma->vm_end - end) >> PAGE_SHIFT);
			exporter = vma;
			importer = next;
		}

		/*
		 * Easily overlooked: when mprotect shifts the boundary,
		 * make sure the expanding vma has anon_vma set if the
		 * shrinking vma had, to cover any anon pages imported.
		 */
		if (exporter && exporter->anon_vma && !importer->anon_vma) {
			if (anon_vma_clone(importer, exporter))
				return -ENOMEM;
			importer->anon_vma = exporter->anon_vma;
		}
	}

	if (file) {
		mapping = file->f_mapping;
		if (!(vma->vm_flags & VM_NONLINEAR))
			root = &mapping->i_mmap;
		spin_lock(&mapping->i_mmap_lock);
		if (importer &&
		    vma->vm_truncate_count != next->vm_truncate_count) {
			/*
			 * unmap_mapping_range might be in progress:
			 * ensure that the expanding vma is rescanned.
			 */
			importer->vm_truncate_count = 0;
		}
		if (insert) {
			insert->vm_truncate_count = vma->vm_truncate_count;
			/*
			 * Put into prio_tree now, so instantiated pages
			 * are visible to arm/parisc __flush_dcache_page
			 * throughout; but we cannot insert into address
			 * space until vma start or end is updated.
			 */
			__vma_link_file(insert);
		}
	}

	vma_adjust_trans_huge(vma, start, end, adjust_next);

	/*
	 * When changing only vma->vm_end, we don't really need anon_vma
	 * lock. This is a fairly rare case by itself, but the anon_vma
	 * lock may be shared between many sibling processes.  Skipping
	 * the lock for brk adjustments makes a difference sometimes.
	 */
	if (vma->anon_vma && (insert || importer || start != vma->vm_start)) {
		anon_vma = vma->anon_vma;
		VM_BUG_ON(adjust_next && next->anon_vma &&
			  anon_vma != next->anon_vma);
	} else if (adjust_next && next->anon_vma)
		anon_vma = next->anon_vma;
	if (anon_vma)
		anon_vma_lock(anon_vma);

	if (root) {
		flush_dcache_mmap_lock(mapping);
		vma_prio_tree_remove(vma, root);
		if (adjust_next)
			vma_prio_tree_remove(next, root);
	}

	vma->vm_start = start;
	vma->vm_end = end;
	vma->vm_pgoff = pgoff;
	if (adjust_next) {
		next->vm_start += adjust_next << PAGE_SHIFT;
		next->vm_pgoff += adjust_next;
	}

	if (root) {
		if (adjust_next)
			vma_prio_tree_insert(next, root);
		vma_prio_tree_insert(vma, root);
		flush_dcache_mmap_unlock(mapping);
	}

	if (remove_next) {
		/*
		 * vma_merge has merged next into vma, and needs
		 * us to remove next before dropping the locks.
		 */
		__vma_unlink(mm, next, vma);
		if (file)
			__remove_shared_vm_struct(next, file, mapping);
	} else if (insert) {
		/*
		 * split_vma has split insert from vma, and needs
		 * us to insert it before dropping the locks
		 * (it may either follow vma or precede it).
		 */
		__insert_vm_struct(mm, insert);
	}

	if (anon_vma)
		anon_vma_unlock(anon_vma);
	if (mapping)
		spin_unlock(&mapping->i_mmap_lock);

	if (remove_next) {
		if (file) {
			fput(file);
			if (next->vm_flags & VM_EXECUTABLE)
				removed_exe_file_vma(mm);
		}
		if (next->anon_vma)
			anon_vma_merge(vma, next);
		mm->map_count--;
		mpol_put(vma_policy(next));
		kmem_cache_free(vm_area_cachep, next);
		/*
		 * In mprotect's case 6 (see comments on vma_merge),
		 * we must remove another next too. It would clutter
		 * up the code too much to do both in one go.
		 */
		if (remove_next == 2) {
			next = vma->vm_next;
			goto again;
		}
	}

	validate_mm(mm);

	return 0;
}