#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct bfd_link_info {int dummy; } ;
typedef  int /*<<< orphan*/  file_ptr ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_7__ {int external_ext_size; } ;
struct TYPE_10__ {TYPE_2__ debug_swap; } ;
struct TYPE_8__ {int iextMax; scalar_t__ issExtMax; scalar_t__ cbSsExtOffset; scalar_t__ cbExtOffset; } ;
struct TYPE_6__ {TYPE_3__ symbolic_header; } ;
struct TYPE_9__ {TYPE_1__ debug_info; } ;
typedef  TYPE_3__ HDRR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TRUE ; 
 int bfd_bread (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_get_symcount (int /*<<< orphan*/ *) ; 
 void* bfd_malloc (int) ; 
 scalar_t__ bfd_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* ecoff_backend (int /*<<< orphan*/ *) ; 
 TYPE_4__* ecoff_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecoff_link_add_externals (int /*<<< orphan*/ *,struct bfd_link_info*,void*,char*) ; 
 int /*<<< orphan*/  ecoff_slurp_symbolic_header (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (void*) ; 

__attribute__((used)) static bfd_boolean
ecoff_link_add_object_symbols (bfd *abfd, struct bfd_link_info *info)
{
  HDRR *symhdr;
  bfd_size_type external_ext_size;
  void * external_ext = NULL;
  bfd_size_type esize;
  char *ssext = NULL;
  bfd_boolean result;

  if (! ecoff_slurp_symbolic_header (abfd))
    return FALSE;

  /* If there are no symbols, we don't want it.  */
  if (bfd_get_symcount (abfd) == 0)
    return TRUE;

  symhdr = &ecoff_data (abfd)->debug_info.symbolic_header;

  /* Read in the external symbols and external strings.  */
  external_ext_size = ecoff_backend (abfd)->debug_swap.external_ext_size;
  esize = symhdr->iextMax * external_ext_size;
  external_ext = bfd_malloc (esize);
  if (external_ext == NULL && esize != 0)
    goto error_return;

  if (bfd_seek (abfd, (file_ptr) symhdr->cbExtOffset, SEEK_SET) != 0
      || bfd_bread (external_ext, esize, abfd) != esize)
    goto error_return;

  ssext = bfd_malloc ((bfd_size_type) symhdr->issExtMax);
  if (ssext == NULL && symhdr->issExtMax != 0)
    goto error_return;

  if (bfd_seek (abfd, (file_ptr) symhdr->cbSsExtOffset, SEEK_SET) != 0
      || (bfd_bread (ssext, (bfd_size_type) symhdr->issExtMax, abfd)
	  != (bfd_size_type) symhdr->issExtMax))
    goto error_return;

  result = ecoff_link_add_externals (abfd, info, external_ext, ssext);

  if (ssext != NULL)
    free (ssext);
  if (external_ext != NULL)
    free (external_ext);
  return result;

 error_return:
  if (ssext != NULL)
    free (ssext);
  if (external_ext != NULL)
    free (external_ext);
  return FALSE;
}