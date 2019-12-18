#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_size; } ;
typedef  int flagword ;
typedef  int /*<<< orphan*/  bfd_target ;
struct TYPE_11__ {void* any; } ;
struct TYPE_12__ {int /*<<< orphan*/  const* xvec; TYPE_1__ tdata; int /*<<< orphan*/  symcount; scalar_t__ target_defaulted; } ;
typedef  TYPE_2__ bfd ;
struct TYPE_13__ {scalar_t__ filepos; int /*<<< orphan*/  size; scalar_t__ vma; } ;
typedef  TYPE_3__ asection ;
struct TYPE_14__ {scalar_t__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIN_SYMS ; 
 int SEC_ALLOC ; 
 int SEC_DATA ; 
 int SEC_HAS_CONTENTS ; 
 int SEC_LOAD ; 
 scalar_t__ bfd_arch_unknown ; 
 int /*<<< orphan*/  bfd_error_system_call ; 
 int /*<<< orphan*/  bfd_error_wrong_format ; 
 scalar_t__ bfd_external_binary_architecture ; 
 int /*<<< orphan*/  bfd_external_machine ; 
 TYPE_9__* bfd_get_arch_info (TYPE_2__*) ; 
 int /*<<< orphan*/  bfd_lookup_arch (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_3__* bfd_make_section_with_flags (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  bfd_set_arch_info (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_stat (TYPE_2__*,struct stat*) ; 

__attribute__((used)) static const bfd_target *
binary_object_p (bfd *abfd)
{
  struct stat statbuf;
  asection *sec;
  flagword flags;

  if (abfd->target_defaulted)
    {
      bfd_set_error (bfd_error_wrong_format);
      return NULL;
    }

  abfd->symcount = BIN_SYMS;

  /* Find the file size.  */
  if (bfd_stat (abfd, &statbuf) < 0)
    {
      bfd_set_error (bfd_error_system_call);
      return NULL;
    }

  /* One data section.  */
  flags = SEC_ALLOC | SEC_LOAD | SEC_DATA | SEC_HAS_CONTENTS;
  sec = bfd_make_section_with_flags (abfd, ".data", flags);
  if (sec == NULL)
    return NULL;
  sec->vma = 0;
  sec->size = statbuf.st_size;
  sec->filepos = 0;

  abfd->tdata.any = (void *) sec;

  if (bfd_get_arch_info (abfd) != NULL)
    {
      if ((bfd_get_arch_info (abfd)->arch == bfd_arch_unknown)
          && (bfd_external_binary_architecture != bfd_arch_unknown))
        bfd_set_arch_info (abfd, bfd_lookup_arch
			   (bfd_external_binary_architecture, bfd_external_machine));
    }

  return abfd->xvec;
}