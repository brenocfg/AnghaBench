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
struct bfd_link_hash_table {int dummy; } ;
struct coff_link_hash_table {struct bfd_link_hash_table root; } ;
struct coff_link_hash_entry {int dummy; } ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  _bfd_coff_link_hash_newfunc ; 
 int /*<<< orphan*/  _bfd_coff_link_hash_table_init (struct coff_link_hash_table*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct coff_link_hash_table* bfd_malloc (int) ; 
 int /*<<< orphan*/  free (struct coff_link_hash_table*) ; 

struct bfd_link_hash_table *
_bfd_coff_link_hash_table_create (bfd *abfd)
{
  struct coff_link_hash_table *ret;
  bfd_size_type amt = sizeof (struct coff_link_hash_table);

  ret = bfd_malloc (amt);
  if (ret == NULL)
    return NULL;

  if (! _bfd_coff_link_hash_table_init (ret, abfd,
					_bfd_coff_link_hash_newfunc,
					sizeof (struct coff_link_hash_entry)))
    {
      free (ret);
      return (struct bfd_link_hash_table *) NULL;
    }
  return &ret->root;
}