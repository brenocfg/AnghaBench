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
struct coff_link_hash_entry {int dummy; } ;
struct bfd_link_info {int dummy; } ;
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 char* THUMB2ARM_GLUE_ENTRY_NAME ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char const*) ; 
 char* bfd_malloc (scalar_t__) ; 
 int /*<<< orphan*/  coff_hash_table (struct bfd_link_info*) ; 
 struct coff_link_hash_entry* coff_link_hash_lookup (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static struct coff_link_hash_entry *
find_thumb_glue (struct bfd_link_info *info,
		 const char *name,
		 bfd *input_bfd)
{
  char *tmp_name;
  struct coff_link_hash_entry *myh;
  bfd_size_type amt = strlen (name) + strlen (THUMB2ARM_GLUE_ENTRY_NAME) + 1;

  tmp_name = bfd_malloc (amt);

  BFD_ASSERT (tmp_name);

  sprintf (tmp_name, THUMB2ARM_GLUE_ENTRY_NAME, name);

  myh = coff_link_hash_lookup
    (coff_hash_table (info), tmp_name, FALSE, FALSE, TRUE);

  if (myh == NULL)
    /* xgettext:c-format */
    _bfd_error_handler (_("%B: unable to find THUMB glue '%s' for `%s'"),
			input_bfd, tmp_name, name);

  free (tmp_name);

  return myh;
}