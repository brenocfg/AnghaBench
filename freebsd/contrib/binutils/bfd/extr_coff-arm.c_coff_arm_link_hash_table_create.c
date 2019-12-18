#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct coff_link_hash_entry {int dummy; } ;
struct bfd_link_hash_table {int dummy; } ;
struct TYPE_2__ {struct bfd_link_hash_table root; } ;
struct coff_arm_link_hash_table {TYPE_1__ root; int /*<<< orphan*/ * bfd_of_glue_owner; scalar_t__ arm_glue_size; scalar_t__ thumb_glue_size; } ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  _bfd_coff_link_hash_newfunc ; 
 int /*<<< orphan*/  _bfd_coff_link_hash_table_init (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct coff_arm_link_hash_table* bfd_malloc (int) ; 
 int /*<<< orphan*/  free (struct coff_arm_link_hash_table*) ; 

__attribute__((used)) static struct bfd_link_hash_table *
coff_arm_link_hash_table_create (bfd * abfd)
{
  struct coff_arm_link_hash_table * ret;
  bfd_size_type amt = sizeof (struct coff_arm_link_hash_table);

  ret = bfd_malloc (amt);
  if (ret == NULL)
    return NULL;

  if (!_bfd_coff_link_hash_table_init (&ret->root,
				       abfd,
				       _bfd_coff_link_hash_newfunc,
				       sizeof (struct coff_link_hash_entry)))
    {
      free (ret);
      return NULL;
    }

  ret->thumb_glue_size   = 0;
  ret->arm_glue_size     = 0;
  ret->bfd_of_glue_owner = NULL;

  return & ret->root.root;
}