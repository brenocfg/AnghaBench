#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_18__ {unsigned int sh_info; int sh_size; int /*<<< orphan*/  sh_link; int /*<<< orphan*/  sh_offset; } ;
struct TYPE_19__ {unsigned int cverrefs; unsigned int cverdefs; TYPE_3__* verdef; TYPE_5__ dynverdef_hdr; TYPE_1__* verref; TYPE_5__ dynverref_hdr; } ;
struct TYPE_17__ {size_t vda_next; struct TYPE_17__* vda_nextptr; int /*<<< orphan*/ * vda_nodename; int /*<<< orphan*/  vda_name; } ;
struct TYPE_16__ {unsigned int vd_ndx; size_t vd_next; unsigned int vd_cnt; size_t vd_aux; int /*<<< orphan*/ * vd_nodename; TYPE_4__* vd_auxptr; struct TYPE_16__* vd_nextdef; int /*<<< orphan*/ * vd_bfd; scalar_t__ vd_flags; int /*<<< orphan*/  vd_version; } ;
struct TYPE_15__ {size_t vna_next; unsigned int vna_other; struct TYPE_15__* vna_nextptr; int /*<<< orphan*/ * vna_nodename; int /*<<< orphan*/  vna_name; } ;
struct TYPE_14__ {unsigned int vn_cnt; size_t vn_aux; size_t vn_next; struct TYPE_14__* vn_nextref; TYPE_2__* vn_auxptr; int /*<<< orphan*/ * vn_filename; int /*<<< orphan*/  vn_file; int /*<<< orphan*/ * vn_bfd; } ;
typedef  TYPE_1__ Elf_Internal_Verneed ;
typedef  TYPE_2__ Elf_Internal_Vernaux ;
typedef  TYPE_3__ Elf_Internal_Verdef ;
typedef  TYPE_4__ Elf_Internal_Verdaux ;
typedef  TYPE_5__ Elf_Internal_Shdr ;
typedef  int /*<<< orphan*/  Elf_External_Verneed ;
typedef  int /*<<< orphan*/  Elf_External_Vernaux ;
typedef  int /*<<< orphan*/  Elf_External_Verdef ;
typedef  int /*<<< orphan*/  Elf_External_Verdaux ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ TRUE ; 
 int VERSYM_VERSION ; 
 int /*<<< orphan*/  VER_DEF_CURRENT ; 
 int /*<<< orphan*/  _bfd_elf_swap_verdaux_in (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  _bfd_elf_swap_verdef_in (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  _bfd_elf_swap_vernaux_in (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  _bfd_elf_swap_verneed_in (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_4__* bfd_alloc (int /*<<< orphan*/ *,int) ; 
 void* bfd_alloc2 (int /*<<< orphan*/ *,unsigned int,int) ; 
 int bfd_bread (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bfd_elf_get_dt_soname (int /*<<< orphan*/ *) ; 
 void* bfd_elf_string_from_elf_section (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bfd_malloc (int) ; 
 scalar_t__ bfd_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* bfd_zalloc2 (int /*<<< orphan*/ *,unsigned int,int) ; 
 scalar_t__ elf_dynverdef (int /*<<< orphan*/ *) ; 
 scalar_t__ elf_dynverref (int /*<<< orphan*/ *) ; 
 TYPE_8__* elf_tdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,int) ; 

bfd_boolean
_bfd_elf_slurp_version_tables (bfd *abfd, bfd_boolean default_imported_symver)
{
  bfd_byte *contents = NULL;
  unsigned int freeidx = 0;

  if (elf_dynverref (abfd) != 0)
    {
      Elf_Internal_Shdr *hdr;
      Elf_External_Verneed *everneed;
      Elf_Internal_Verneed *iverneed;
      unsigned int i;
      bfd_byte *contents_end;

      hdr = &elf_tdata (abfd)->dynverref_hdr;

      elf_tdata (abfd)->verref = bfd_zalloc2 (abfd, hdr->sh_info,
					      sizeof (Elf_Internal_Verneed));
      if (elf_tdata (abfd)->verref == NULL)
	goto error_return;

      elf_tdata (abfd)->cverrefs = hdr->sh_info;

      contents = bfd_malloc (hdr->sh_size);
      if (contents == NULL)
	{
error_return_verref:
	  elf_tdata (abfd)->verref = NULL;
	  elf_tdata (abfd)->cverrefs = 0;
	  goto error_return;
	}
      if (bfd_seek (abfd, hdr->sh_offset, SEEK_SET) != 0
	  || bfd_bread (contents, hdr->sh_size, abfd) != hdr->sh_size)
	goto error_return_verref;

      if (hdr->sh_info && hdr->sh_size < sizeof (Elf_External_Verneed))
	goto error_return_verref;

      BFD_ASSERT (sizeof (Elf_External_Verneed)
		  == sizeof (Elf_External_Vernaux));
      contents_end = contents + hdr->sh_size - sizeof (Elf_External_Verneed);
      everneed = (Elf_External_Verneed *) contents;
      iverneed = elf_tdata (abfd)->verref;
      for (i = 0; i < hdr->sh_info; i++, iverneed++)
	{
	  Elf_External_Vernaux *evernaux;
	  Elf_Internal_Vernaux *ivernaux;
	  unsigned int j;

	  _bfd_elf_swap_verneed_in (abfd, everneed, iverneed);

	  iverneed->vn_bfd = abfd;

	  iverneed->vn_filename =
	    bfd_elf_string_from_elf_section (abfd, hdr->sh_link,
					     iverneed->vn_file);
	  if (iverneed->vn_filename == NULL)
	    goto error_return_verref;

	  if (iverneed->vn_cnt == 0)
	    iverneed->vn_auxptr = NULL;
	  else
	    {
	      iverneed->vn_auxptr = bfd_alloc2 (abfd, iverneed->vn_cnt,
						sizeof (Elf_Internal_Vernaux));
	      if (iverneed->vn_auxptr == NULL)
		goto error_return_verref;
	    }

	  if (iverneed->vn_aux
	      > (size_t) (contents_end - (bfd_byte *) everneed))
	    goto error_return_verref;

	  evernaux = ((Elf_External_Vernaux *)
		      ((bfd_byte *) everneed + iverneed->vn_aux));
	  ivernaux = iverneed->vn_auxptr;
	  for (j = 0; j < iverneed->vn_cnt; j++, ivernaux++)
	    {
	      _bfd_elf_swap_vernaux_in (abfd, evernaux, ivernaux);

	      ivernaux->vna_nodename =
		bfd_elf_string_from_elf_section (abfd, hdr->sh_link,
						 ivernaux->vna_name);
	      if (ivernaux->vna_nodename == NULL)
		goto error_return_verref;

	      if (j + 1 < iverneed->vn_cnt)
		ivernaux->vna_nextptr = ivernaux + 1;
	      else
		ivernaux->vna_nextptr = NULL;

	      if (ivernaux->vna_next
		  > (size_t) (contents_end - (bfd_byte *) evernaux))
		goto error_return_verref;

	      evernaux = ((Elf_External_Vernaux *)
			  ((bfd_byte *) evernaux + ivernaux->vna_next));

	      if (ivernaux->vna_other > freeidx)
		freeidx = ivernaux->vna_other;
	    }

	  if (i + 1 < hdr->sh_info)
	    iverneed->vn_nextref = iverneed + 1;
	  else
	    iverneed->vn_nextref = NULL;

	  if (iverneed->vn_next
	      > (size_t) (contents_end - (bfd_byte *) everneed))
	    goto error_return_verref;

	  everneed = ((Elf_External_Verneed *)
		      ((bfd_byte *) everneed + iverneed->vn_next));
	}

      free (contents);
      contents = NULL;
    }

  if (elf_dynverdef (abfd) != 0)
    {
      Elf_Internal_Shdr *hdr;
      Elf_External_Verdef *everdef;
      Elf_Internal_Verdef *iverdef;
      Elf_Internal_Verdef *iverdefarr;
      Elf_Internal_Verdef iverdefmem;
      unsigned int i;
      unsigned int maxidx;
      bfd_byte *contents_end_def, *contents_end_aux;

      hdr = &elf_tdata (abfd)->dynverdef_hdr;

      contents = bfd_malloc (hdr->sh_size);
      if (contents == NULL)
	goto error_return;
      if (bfd_seek (abfd, hdr->sh_offset, SEEK_SET) != 0
	  || bfd_bread (contents, hdr->sh_size, abfd) != hdr->sh_size)
	goto error_return;

      if (hdr->sh_info && hdr->sh_size < sizeof (Elf_External_Verdef))
	goto error_return;

      BFD_ASSERT (sizeof (Elf_External_Verdef)
		  >= sizeof (Elf_External_Verdaux));
      contents_end_def = contents + hdr->sh_size
			 - sizeof (Elf_External_Verdef);
      contents_end_aux = contents + hdr->sh_size
			 - sizeof (Elf_External_Verdaux);

      /* We know the number of entries in the section but not the maximum
	 index.  Therefore we have to run through all entries and find
	 the maximum.  */
      everdef = (Elf_External_Verdef *) contents;
      maxidx = 0;
      for (i = 0; i < hdr->sh_info; ++i)
	{
	  _bfd_elf_swap_verdef_in (abfd, everdef, &iverdefmem);

	  if ((iverdefmem.vd_ndx & ((unsigned) VERSYM_VERSION)) > maxidx)
	    maxidx = iverdefmem.vd_ndx & ((unsigned) VERSYM_VERSION);

	  if (iverdefmem.vd_next
	      > (size_t) (contents_end_def - (bfd_byte *) everdef))
	    goto error_return;

	  everdef = ((Elf_External_Verdef *)
		     ((bfd_byte *) everdef + iverdefmem.vd_next));
	}

      if (default_imported_symver)
	{
	  if (freeidx > maxidx)
	    maxidx = ++freeidx;
	  else
	    freeidx = ++maxidx;
	}
      elf_tdata (abfd)->verdef = bfd_zalloc2 (abfd, maxidx,
					      sizeof (Elf_Internal_Verdef));
      if (elf_tdata (abfd)->verdef == NULL)
	goto error_return;

      elf_tdata (abfd)->cverdefs = maxidx;

      everdef = (Elf_External_Verdef *) contents;
      iverdefarr = elf_tdata (abfd)->verdef;
      for (i = 0; i < hdr->sh_info; i++)
	{
	  Elf_External_Verdaux *everdaux;
	  Elf_Internal_Verdaux *iverdaux;
	  unsigned int j;

	  _bfd_elf_swap_verdef_in (abfd, everdef, &iverdefmem);

	  if ((iverdefmem.vd_ndx & VERSYM_VERSION) == 0)
	    {
error_return_verdef:
	      elf_tdata (abfd)->verdef = NULL;
	      elf_tdata (abfd)->cverdefs = 0;
	      goto error_return;
	    }

	  iverdef = &iverdefarr[(iverdefmem.vd_ndx & VERSYM_VERSION) - 1];
	  memcpy (iverdef, &iverdefmem, sizeof (Elf_Internal_Verdef));

	  iverdef->vd_bfd = abfd;

	  if (iverdef->vd_cnt == 0)
	    iverdef->vd_auxptr = NULL;
	  else
	    {
	      iverdef->vd_auxptr = bfd_alloc2 (abfd, iverdef->vd_cnt,
					       sizeof (Elf_Internal_Verdaux));
	      if (iverdef->vd_auxptr == NULL)
		goto error_return_verdef;
	    }

	  if (iverdef->vd_aux
	      > (size_t) (contents_end_aux - (bfd_byte *) everdef))
	    goto error_return_verdef;

	  everdaux = ((Elf_External_Verdaux *)
		      ((bfd_byte *) everdef + iverdef->vd_aux));
	  iverdaux = iverdef->vd_auxptr;
	  for (j = 0; j < iverdef->vd_cnt; j++, iverdaux++)
	    {
	      _bfd_elf_swap_verdaux_in (abfd, everdaux, iverdaux);

	      iverdaux->vda_nodename =
		bfd_elf_string_from_elf_section (abfd, hdr->sh_link,
						 iverdaux->vda_name);
	      if (iverdaux->vda_nodename == NULL)
		goto error_return_verdef;

	      if (j + 1 < iverdef->vd_cnt)
		iverdaux->vda_nextptr = iverdaux + 1;
	      else
		iverdaux->vda_nextptr = NULL;

	      if (iverdaux->vda_next
		  > (size_t) (contents_end_aux - (bfd_byte *) everdaux))
		goto error_return_verdef;

	      everdaux = ((Elf_External_Verdaux *)
			  ((bfd_byte *) everdaux + iverdaux->vda_next));
	    }

	  if (iverdef->vd_cnt)
	    iverdef->vd_nodename = iverdef->vd_auxptr->vda_nodename;

	  if ((size_t) (iverdef - iverdefarr) + 1 < maxidx)
	    iverdef->vd_nextdef = iverdef + 1;
	  else
	    iverdef->vd_nextdef = NULL;

	  everdef = ((Elf_External_Verdef *)
		     ((bfd_byte *) everdef + iverdef->vd_next));
	}

      free (contents);
      contents = NULL;
    }
  else if (default_imported_symver)
    {
      if (freeidx < 3)
	freeidx = 3;
      else
	freeidx++;

      elf_tdata (abfd)->verdef = bfd_zalloc2 (abfd, freeidx,
					      sizeof (Elf_Internal_Verdef));
      if (elf_tdata (abfd)->verdef == NULL)
	goto error_return;

      elf_tdata (abfd)->cverdefs = freeidx;
    }

  /* Create a default version based on the soname.  */
  if (default_imported_symver)
    {
      Elf_Internal_Verdef *iverdef;
      Elf_Internal_Verdaux *iverdaux;

      iverdef = &elf_tdata (abfd)->verdef[freeidx - 1];;

      iverdef->vd_version = VER_DEF_CURRENT;
      iverdef->vd_flags = 0;
      iverdef->vd_ndx = freeidx;
      iverdef->vd_cnt = 1;

      iverdef->vd_bfd = abfd;

      iverdef->vd_nodename = bfd_elf_get_dt_soname (abfd);
      if (iverdef->vd_nodename == NULL)
	goto error_return_verdef;
      iverdef->vd_nextdef = NULL;
      iverdef->vd_auxptr = bfd_alloc (abfd, sizeof (Elf_Internal_Verdaux));
      if (iverdef->vd_auxptr == NULL)
	goto error_return_verdef;

      iverdaux = iverdef->vd_auxptr;
      iverdaux->vda_nodename = iverdef->vd_nodename;
      iverdaux->vda_nextptr = NULL;
    }

  return TRUE;

 error_return:
  if (contents != NULL)
    free (contents);
  return FALSE;
}