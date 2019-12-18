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
struct TYPE_3__ {int /*<<< orphan*/  nonexistent_file_ob; int /*<<< orphan*/  nonexistent_file_hash; int /*<<< orphan*/  dir_hash; int /*<<< orphan*/  file_hash; } ;
typedef  TYPE_1__ cpp_reader ;

/* Variables and functions */
 int /*<<< orphan*/  htab_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
_cpp_cleanup_files (cpp_reader *pfile)
{
  htab_delete (pfile->file_hash);
  htab_delete (pfile->dir_hash);
  htab_delete (pfile->nonexistent_file_hash);
  obstack_free (&pfile->nonexistent_file_ob, 0);
}