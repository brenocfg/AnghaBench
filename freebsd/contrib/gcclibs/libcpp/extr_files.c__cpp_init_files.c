#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  nonexistent_file_ob; void* nonexistent_file_hash; void* dir_hash; void* file_hash; } ;
typedef  TYPE_1__ cpp_reader ;

/* Variables and functions */
 int /*<<< orphan*/  _obstack_begin (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void* (*) (long),void (*) (void*)) ; 
 int /*<<< orphan*/  allocate_file_hash_entries (TYPE_1__*) ; 
 int /*<<< orphan*/  file_hash_eq ; 
 int /*<<< orphan*/  file_hash_hash ; 
 scalar_t__ free ; 
 void* htab_create_alloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  htab_hash_string ; 
 int /*<<< orphan*/  nonexistent_file_hash_eq ; 
 int /*<<< orphan*/  xcalloc ; 
 scalar_t__ xmalloc ; 

void
_cpp_init_files (cpp_reader *pfile)
{
  pfile->file_hash = htab_create_alloc (127, file_hash_hash, file_hash_eq,
					NULL, xcalloc, free);
  pfile->dir_hash = htab_create_alloc (127, file_hash_hash, file_hash_eq,
					NULL, xcalloc, free);
  allocate_file_hash_entries (pfile);
  pfile->nonexistent_file_hash = htab_create_alloc (127, htab_hash_string,
						    nonexistent_file_hash_eq,
						    NULL, xcalloc, free);
  _obstack_begin (&pfile->nonexistent_file_ob, 0, 0,
		  (void *(*) (long)) xmalloc,
		  (void (*) (void *)) free);
}