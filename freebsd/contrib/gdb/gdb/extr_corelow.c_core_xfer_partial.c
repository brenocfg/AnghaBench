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
struct target_ops {int (* to_xfer_memory ) (int,void*,int,int,int /*<<< orphan*/ *,struct target_ops*) ;TYPE_1__* beneath; } ;
struct bfd_section {int dummy; } ;
typedef  int /*<<< orphan*/  file_ptr ;
typedef  enum target_object { ____Placeholder_target_object } target_object ;
typedef  int bfd_size_type ;
typedef  int ULONGEST ;
struct TYPE_2__ {int (* to_xfer_partial ) (TYPE_1__*,int,char const*,void*,void const*,int,int) ;} ;
typedef  int LONGEST ;

/* Variables and functions */
#define  TARGET_OBJECT_AUXV 130 
#define  TARGET_OBJECT_DIRTY 129 
#define  TARGET_OBJECT_MEMORY 128 
 struct bfd_section* bfd_get_section_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bfd_get_section_contents (int /*<<< orphan*/ ,struct bfd_section*,void*,int /*<<< orphan*/ ,int) ; 
 int bfd_section_size (int /*<<< orphan*/ ,struct bfd_section*) ; 
 int /*<<< orphan*/  core_bfd ; 
 int stub1 (int,void*,int,int,int /*<<< orphan*/ *,struct target_ops*) ; 
 int stub2 (int,void const*,int,int,int /*<<< orphan*/ *,struct target_ops*) ; 
 int stub3 (int,void*,int,int,int /*<<< orphan*/ *,struct target_ops*) ; 
 int stub4 (int,void const*,int,int,int /*<<< orphan*/ *,struct target_ops*) ; 
 int stub5 (TYPE_1__*,int,char const*,void*,void const*,int,int) ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static LONGEST
core_xfer_partial (struct target_ops *ops, enum target_object object,
		   const char *annex, void *readbuf,
		   const void *writebuf, ULONGEST offset, LONGEST len)
{
  switch (object)
    {
    case TARGET_OBJECT_MEMORY:
      if (readbuf)
	return (*ops->to_xfer_memory) (offset, readbuf, len, 0/*read*/,
				       NULL, ops);
      if (writebuf)
	return (*ops->to_xfer_memory) (offset, writebuf, len, 1/*write*/,
				       NULL, ops);
      return -1;

    case TARGET_OBJECT_AUXV:
      if (readbuf)
	{
	  /* When the aux vector is stored in core file, BFD
	     represents this with a fake section called ".auxv".  */

	  struct bfd_section *section;
	  bfd_size_type size;
	  char *contents;

	  section = bfd_get_section_by_name (core_bfd, ".auxv");
	  if (section == NULL)
	    return -1;

	  size = bfd_section_size (core_bfd, section);
	  if (offset >= size)
	    return 0;
	  size -= offset;
	  if (size > len)
	    size = len;
	  if (size > 0 &&
	      ! bfd_get_section_contents (core_bfd, section, readbuf,
					  (file_ptr) offset, size))
	    {
	      warning ("Couldn't read NT_AUXV note in core file.");
	      return -1;
	    }

	  return size;
	}
      return -1;

    case TARGET_OBJECT_DIRTY:
      {
	ULONGEST addr;
	addr = *(ULONGEST*)annex + offset;
	if (readbuf)
	  return (*ops->to_xfer_memory) (addr, readbuf, len, 0/*read*/,
					 NULL, ops);
	if (writebuf)
	  return (*ops->to_xfer_memory) (addr, writebuf, len, 1/*write*/,
					 NULL, ops);
	return -1;
      }

    default:
      if (ops->beneath != NULL)
	return ops->beneath->to_xfer_partial (ops->beneath, object, annex,
					      readbuf, writebuf, offset, len);
      return -1;
    }
}