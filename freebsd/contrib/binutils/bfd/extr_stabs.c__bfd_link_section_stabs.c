#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct stab_section_info {int* cumulative_skips; int* stridxs; struct stab_excl_list* excls; } ;
struct stab_link_includes_totals {scalar_t__ sum_chars; scalar_t__ num_chars; struct stab_link_includes_totals* next; void* symb; } ;
struct stab_link_includes_entry {struct stab_link_includes_totals* totals; } ;
struct stab_info {int /*<<< orphan*/ * strings; TYPE_4__* stabstr; int /*<<< orphan*/  includes; } ;
struct stab_excl_list {int type; struct stab_excl_list* next; scalar_t__ val; int /*<<< orphan*/  offset; } ;
typedef  int flagword ;
typedef  scalar_t__ bfd_vma ;
typedef  int bfd_size_type ;
typedef  char bfd_byte ;
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_8__ {scalar_t__ size; int flags; int rawsize; int /*<<< orphan*/  output_section; } ;
typedef  TYPE_1__ asection ;
struct TYPE_9__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 scalar_t__ FALSE ; 
 scalar_t__ ISDIGIT (char const) ; 
 scalar_t__ N_BINCL ; 
 scalar_t__ N_EINCL ; 
 scalar_t__ N_EXCL ; 
 int SEC_DEBUGGING ; 
 int SEC_EXCLUDE ; 
 int SEC_HAS_CONTENTS ; 
 int SEC_KEEP ; 
 int SEC_LINKER_CREATED ; 
 int SEC_READONLY ; 
 int SEC_RELOC ; 
 int STABSIZE ; 
 int STRDXOFF ; 
 scalar_t__ TRUE ; 
 size_t TYPEOFF ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,long) ; 
 int _bfd_stringtab_add (int /*<<< orphan*/ *,char const*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * _bfd_stringtab_init () ; 
 int /*<<< orphan*/  _bfd_stringtab_size (int /*<<< orphan*/ *) ; 
 void* bfd_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bfd_error_bad_value ; 
 int bfd_get_32 (int /*<<< orphan*/ *,char*) ; 
 struct stab_link_includes_totals* bfd_hash_allocate (int /*<<< orphan*/ *,int) ; 
 scalar_t__ bfd_hash_lookup (int /*<<< orphan*/ *,char const*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bfd_hash_table_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bfd_is_abs_section (int /*<<< orphan*/ ) ; 
 TYPE_4__* bfd_make_section_anyway_with_flags (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  bfd_malloc_and_get_section (int /*<<< orphan*/ *,TYPE_1__*,char**) ; 
 void* bfd_realloc (char*,scalar_t__) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ memcmp (void*,char*,scalar_t__) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  stab_link_includes_newfunc ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,long) ; 

bfd_boolean
_bfd_link_section_stabs (bfd *abfd,
			 struct stab_info *sinfo,
			 asection *stabsec,
			 asection *stabstrsec,
			 void * *psecinfo,
			 bfd_size_type *pstring_offset)
{
  bfd_boolean first;
  bfd_size_type count, amt;
  struct stab_section_info *secinfo;
  bfd_byte *stabbuf = NULL;
  bfd_byte *stabstrbuf = NULL;
  bfd_byte *sym, *symend;
  bfd_size_type stroff, next_stroff, skip;
  bfd_size_type *pstridx;

  if (stabsec->size == 0
      || stabstrsec->size == 0)
    /* This file does not contain stabs debugging information.  */
    return TRUE;

  if (stabsec->size % STABSIZE != 0)
    /* Something is wrong with the format of these stab symbols.
       Don't try to optimize them.  */
    return TRUE;

  if ((stabstrsec->flags & SEC_RELOC) != 0)
    /* We shouldn't see relocations in the strings, and we aren't
       prepared to handle them.  */
    return TRUE;

  if (bfd_is_abs_section (stabsec->output_section)
      || bfd_is_abs_section (stabstrsec->output_section))
    /* At least one of the sections is being discarded from the
       link, so we should just ignore them.  */
    return TRUE;

  first = FALSE;

  if (sinfo->stabstr == NULL)
    {
      flagword flags;

      /* Initialize the stabs information we need to keep track of.  */
      first = TRUE;
      sinfo->strings = _bfd_stringtab_init ();
      if (sinfo->strings == NULL)
	goto error_return;
      /* Make sure the first byte is zero.  */
      (void) _bfd_stringtab_add (sinfo->strings, "", TRUE, TRUE);
      if (! bfd_hash_table_init (&sinfo->includes,
				 stab_link_includes_newfunc,
				 sizeof (struct stab_link_includes_entry)))
	goto error_return;
      flags = (SEC_HAS_CONTENTS | SEC_READONLY | SEC_DEBUGGING
	       | SEC_LINKER_CREATED);
      sinfo->stabstr = bfd_make_section_anyway_with_flags (abfd, ".stabstr",
							   flags);
      if (sinfo->stabstr == NULL)
	goto error_return;
    }

  /* Initialize the information we are going to store for this .stab
     section.  */
  count = stabsec->size / STABSIZE;

  amt = sizeof (struct stab_section_info);
  amt += (count - 1) * sizeof (bfd_size_type);
  *psecinfo = bfd_alloc (abfd, amt);
  if (*psecinfo == NULL)
    goto error_return;

  secinfo = (struct stab_section_info *) *psecinfo;
  secinfo->excls = NULL;
  stabsec->rawsize = stabsec->size;
  secinfo->cumulative_skips = NULL;
  memset (secinfo->stridxs, 0, (size_t) count * sizeof (bfd_size_type));

  /* Read the stabs information from abfd.  */
  if (!bfd_malloc_and_get_section (abfd, stabsec, &stabbuf)
      || !bfd_malloc_and_get_section (abfd, stabstrsec, &stabstrbuf))
    goto error_return;

  /* Look through the stabs symbols, work out the new string indices,
     and identify N_BINCL symbols which can be eliminated.  */
  stroff = 0;
  /* The stabs sections can be split when
     -split-by-reloc/-split-by-file is used.  We must keep track of
     each stab section's place in the single concatenated string
     table.  */
  next_stroff = pstring_offset ? *pstring_offset : 0;
  skip = 0;

  symend = stabbuf + stabsec->size;
  for (sym = stabbuf, pstridx = secinfo->stridxs;
       sym < symend;
       sym += STABSIZE, ++pstridx)
    {
      bfd_size_type symstroff;
      int type;
      const char *string;

      if (*pstridx != 0)
	/* This symbol has already been handled by an N_BINCL pass.  */
	continue;

      type = sym[TYPEOFF];

      if (type == 0)
	{
	  /* Special type 0 stabs indicate the offset to the next
	     string table.  We only copy the very first one.  */
	  stroff = next_stroff;
	  next_stroff += bfd_get_32 (abfd, sym + 8);
	  if (pstring_offset)
	    *pstring_offset = next_stroff;
	  if (! first)
	    {
	      *pstridx = (bfd_size_type) -1;
	      ++skip;
	      continue;
	    }
	  first = FALSE;
	}

      /* Store the string in the hash table, and record the index.  */
      symstroff = stroff + bfd_get_32 (abfd, sym + STRDXOFF);
      if (symstroff >= stabstrsec->size)
	{
	  (*_bfd_error_handler)
	    (_("%B(%A+0x%lx): Stabs entry has invalid string index."),
	     abfd, stabsec, (long) (sym - stabbuf));
	  bfd_set_error (bfd_error_bad_value);
	  goto error_return;
	}
      string = (char *) stabstrbuf + symstroff;
      *pstridx = _bfd_stringtab_add (sinfo->strings, string, TRUE, TRUE);

      /* An N_BINCL symbol indicates the start of the stabs entries
	 for a header file.  We need to scan ahead to the next N_EINCL
	 symbol, ignoring nesting, adding up all the characters in the
	 symbol names, not including the file numbers in types (the
	 first number after an open parenthesis).  */
      if (type == (int) N_BINCL)
	{
	  bfd_vma sum_chars;
	  bfd_vma num_chars;
	  bfd_vma buf_len = 0;
	  char * symb;
	  char * symb_rover;
	  int nest;
	  bfd_byte * incl_sym;
	  struct stab_link_includes_entry * incl_entry;
	  struct stab_link_includes_totals * t;
	  struct stab_excl_list * ne;

	  symb = symb_rover = NULL;
	  sum_chars = num_chars = 0;
	  nest = 0;

	  for (incl_sym = sym + STABSIZE;
	       incl_sym < symend;
	       incl_sym += STABSIZE)
	    {
	      int incl_type;

	      incl_type = incl_sym[TYPEOFF];
	      if (incl_type == 0)
		break;
	      else if (incl_type == (int) N_EXCL)
		continue;
	      else if (incl_type == (int) N_EINCL)
		{
		  if (nest == 0)
		    break;
		  --nest;
		}
	      else if (incl_type == (int) N_BINCL)
		++nest;
	      else if (nest == 0)
		{
		  const char *str;

		  str = ((char *) stabstrbuf
			 + stroff
			 + bfd_get_32 (abfd, incl_sym + STRDXOFF));
		  for (; *str != '\0'; str++)
		    {
		      if (num_chars >= buf_len)
			{
			  buf_len += 32 * 1024;
			  symb = bfd_realloc (symb, buf_len);
			  if (symb == NULL)
			    goto error_return;
			  symb_rover = symb + num_chars;
			}
		      * symb_rover ++ = * str;
		      sum_chars += *str;
		      num_chars ++;
		      if (*str == '(')
			{
			  /* Skip the file number.  */
			  ++str;
			  while (ISDIGIT (*str))
			    ++str;
			  --str;
			}
		    }
		}
	    }

	  BFD_ASSERT (num_chars == (bfd_vma) (symb_rover - symb));

	  /* If we have already included a header file with the same
	     value, then replaced this one with an N_EXCL symbol.  */
	  incl_entry = (struct stab_link_includes_entry * )
	    bfd_hash_lookup (&sinfo->includes, string, TRUE, TRUE);
	  if (incl_entry == NULL)
	    goto error_return;

	  for (t = incl_entry->totals; t != NULL; t = t->next)
	    if (t->sum_chars == sum_chars
		&& t->num_chars == num_chars
		&& memcmp (t->symb, symb, num_chars) == 0)
	      break;

	  /* Record this symbol, so that we can set the value
	     correctly.  */
	  amt = sizeof *ne;
	  ne = bfd_alloc (abfd, amt);
	  if (ne == NULL)
	    goto error_return;
	  ne->offset = sym - stabbuf;
	  ne->val = sum_chars;
	  ne->type = (int) N_BINCL;
	  ne->next = secinfo->excls;
	  secinfo->excls = ne;

	  if (t == NULL)
	    {
	      /* This is the first time we have seen this header file
		 with this set of stabs strings.  */
	      t = bfd_hash_allocate (&sinfo->includes, sizeof *t);
	      if (t == NULL)
		goto error_return;
	      t->sum_chars = sum_chars;
	      t->num_chars = num_chars;
	      t->symb = bfd_realloc (symb, num_chars); /* Trim data down.  */
	      t->next = incl_entry->totals;
	      incl_entry->totals = t;
	    }
	  else
	    {
	      bfd_size_type *incl_pstridx;

	      /* We have seen this header file before.  Tell the final
		 pass to change the type to N_EXCL.  */
	      ne->type = (int) N_EXCL;

	      /* Free off superfluous symbols.  */
	      free (symb);

	      /* Mark the skipped symbols.  */

	      nest = 0;
	      for (incl_sym = sym + STABSIZE, incl_pstridx = pstridx + 1;
		   incl_sym < symend;
		   incl_sym += STABSIZE, ++incl_pstridx)
		{
		  int incl_type;

		  incl_type = incl_sym[TYPEOFF];

		  if (incl_type == (int) N_EINCL)
		    {
		      if (nest == 0)
			{
			  *incl_pstridx = (bfd_size_type) -1;
			  ++skip;
			  break;
			}
		      --nest;
		    }
		  else if (incl_type == (int) N_BINCL)
		    ++nest;
		  else if (incl_type == (int) N_EXCL)
		    /* Keep existing exclusion marks.  */
		    continue;
		  else if (nest == 0)
		    {
		      *incl_pstridx = (bfd_size_type) -1;
		      ++skip;
		    }
		}
	    }
	}
    }

  free (stabbuf);
  stabbuf = NULL;
  free (stabstrbuf);
  stabstrbuf = NULL;

  /* We need to set the section sizes such that the linker will
     compute the output section sizes correctly.  We set the .stab
     size to not include the entries we don't want.  We set
     SEC_EXCLUDE for the .stabstr section, so that it will be dropped
     from the link.  We record the size of the strtab in the first
     .stabstr section we saw, and make sure we don't set SEC_EXCLUDE
     for that section.  */
  stabsec->size = (count - skip) * STABSIZE;
  if (stabsec->size == 0)
    stabsec->flags |= SEC_EXCLUDE | SEC_KEEP;
  stabstrsec->flags |= SEC_EXCLUDE | SEC_KEEP;
  sinfo->stabstr->size = _bfd_stringtab_size (sinfo->strings);

  /* Calculate the `cumulative_skips' array now that stabs have been
     deleted for this section.  */

  if (skip != 0)
    {
      bfd_size_type i, offset;
      bfd_size_type *pskips;

      amt = count * sizeof (bfd_size_type);
      secinfo->cumulative_skips = bfd_alloc (abfd, amt);
      if (secinfo->cumulative_skips == NULL)
	goto error_return;

      pskips = secinfo->cumulative_skips;
      pstridx = secinfo->stridxs;
      offset = 0;

      for (i = 0; i < count; i++, pskips++, pstridx++)
	{
	  *pskips = offset;
	  if (*pstridx == (bfd_size_type) -1)
	    offset += STABSIZE;
	}

      BFD_ASSERT (offset != 0);
    }

  return TRUE;

 error_return:
  if (stabbuf != NULL)
    free (stabbuf);
  if (stabstrbuf != NULL)
    free (stabstrbuf);
  return FALSE;
}