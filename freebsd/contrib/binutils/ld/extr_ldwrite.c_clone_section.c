#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* section; scalar_t__ value; } ;
struct TYPE_9__ {TYPE_1__ def; } ;
struct bfd_link_hash_entry {TYPE_2__ u; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_10__ {int /*<<< orphan*/  alignment_power; scalar_t__ reloc_count; scalar_t__ orelocation; struct TYPE_10__* output_section; int /*<<< orphan*/  output_offset; scalar_t__ size; int /*<<< orphan*/  lma; int /*<<< orphan*/  user_set_vma; int /*<<< orphan*/  vma; int /*<<< orphan*/  flags; } ;
typedef  TYPE_3__ asection ;
struct TYPE_11__ {int /*<<< orphan*/  hash; } ;

/* Variables and functions */
 scalar_t__ CONST_STRNEQ (char const*,char*) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ ISDIGIT (char) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ bfd_family_coff (int /*<<< orphan*/ *) ; 
 char* bfd_get_unique_section_name (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  bfd_link_hash_defined ; 
 struct bfd_link_hash_entry* bfd_link_hash_lookup (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* bfd_make_section_anyway (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  einfo (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_4__ link_info ; 
 int /*<<< orphan*/  memcpy (char*,char const*,unsigned int) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char const*) ; 
 char* xmalloc (unsigned int) ; 

__attribute__((used)) static asection *
clone_section (bfd *abfd, asection *s, const char *name, int *count)
{
  char *tname;
  char *sname;
  unsigned int len;	
  asection *n;
  struct bfd_link_hash_entry *h;

  /* Invent a section name from the section name and a dotted numeric
     suffix.   */
  len = strlen (name);
  tname = xmalloc (len + 1);
  memcpy (tname, name, len + 1);
  /* Remove a dotted number suffix, from a previous split link. */
  while (len && ISDIGIT (tname[len-1]))
    len--;
  if (len > 1 && tname[len-1] == '.')
    /* It was a dotted number. */
    tname[len-1] = 0;

  /* We want to use the whole of the original section name for the
     split name, but coff can be restricted to 8 character names.  */
  if (bfd_family_coff (abfd) && strlen (tname) > 5)
    {
      /* Some section names cannot be truncated, as the name is
	 used to locate some other section.  */
      if (CONST_STRNEQ (name, ".stab")
	  || strcmp (name, "$GDB_SYMBOLS$") == 0)
	{
	  einfo (_ ("%F%P: cannot create split section name for %s\n"), name);
	  /* Silence gcc warnings.  einfo exits, so we never reach here.  */
	  return NULL;
	}
      tname[5] = 0;
    }
  
  if ((sname = bfd_get_unique_section_name (abfd, tname, count)) == NULL
      || (n = bfd_make_section_anyway (abfd, sname)) == NULL
      || (h = bfd_link_hash_lookup (link_info.hash,
				    sname, TRUE, TRUE, FALSE)) == NULL)
    {
      einfo (_("%F%P: clone section failed: %E\n"));
      /* Silence gcc warnings.  einfo exits, so we never reach here.  */
      return NULL;
    }
  free (tname);
  
  /* Set up section symbol.  */
  h->type = bfd_link_hash_defined;
  h->u.def.value = 0;
  h->u.def.section = n;

  n->flags = s->flags;
  n->vma = s->vma;
  n->user_set_vma = s->user_set_vma;
  n->lma = s->lma;
  n->size = 0;
  n->output_offset = s->output_offset;
  n->output_section = n;
  n->orelocation = 0;
  n->reloc_count = 0;
  n->alignment_power = s->alignment_power;
  return n;
}