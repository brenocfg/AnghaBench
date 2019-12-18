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
struct TYPE_10__ {unsigned long elf_hash_value; } ;
struct TYPE_8__ {char* string; } ;
struct TYPE_6__ {scalar_t__ link; } ;
struct TYPE_7__ {TYPE_1__ i; } ;
struct TYPE_9__ {scalar_t__ type; TYPE_3__ root; TYPE_2__ u; } ;
struct elf_link_hash_entry {int dynindx; TYPE_5__ u; TYPE_4__ root; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_VER_CHR ; 
 int /*<<< orphan*/  TRUE ; 
 unsigned long bfd_elf_hash (char const*) ; 
 scalar_t__ bfd_link_hash_warning ; 
 char* bfd_malloc (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* strchr (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
elf_collect_hash_codes (struct elf_link_hash_entry *h, void *data)
{
  unsigned long **valuep = data;
  const char *name;
  char *p;
  unsigned long ha;
  char *alc = NULL;

  if (h->root.type == bfd_link_hash_warning)
    h = (struct elf_link_hash_entry *) h->root.u.i.link;

  /* Ignore indirect symbols.  These are added by the versioning code.  */
  if (h->dynindx == -1)
    return TRUE;

  name = h->root.root.string;
  p = strchr (name, ELF_VER_CHR);
  if (p != NULL)
    {
      alc = bfd_malloc (p - name + 1);
      memcpy (alc, name, p - name);
      alc[p - name] = '\0';
      name = alc;
    }

  /* Compute the hash value.  */
  ha = bfd_elf_hash (name);

  /* Store the found hash value in the array given as the argument.  */
  *(*valuep)++ = ha;

  /* And store it in the struct so that we can put it in the hash table
     later.  */
  h->u.elf_hash_value = ha;

  if (alc != NULL)
    free (alc);

  return TRUE;
}