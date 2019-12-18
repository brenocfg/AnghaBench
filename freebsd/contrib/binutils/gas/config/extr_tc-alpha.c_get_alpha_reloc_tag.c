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
struct alpha_reloc_tag {long sequence; int /*<<< orphan*/  string; int /*<<< orphan*/  segment; } ;

/* Variables and functions */
 int ALPHA_RELOC_DIGITS ; 
 int /*<<< orphan*/  alpha_literal_hash ; 
 int /*<<< orphan*/  as_fatal (char const*) ; 
 scalar_t__ hash_find (int /*<<< orphan*/ ,char*) ; 
 char* hash_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  now_seg ; 
 int /*<<< orphan*/  sprintf (char*,char*,long) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 size_t strlen (char*) ; 
 struct alpha_reloc_tag* xcalloc (int,int) ; 

__attribute__((used)) static struct alpha_reloc_tag *
get_alpha_reloc_tag (long sequence)
{
  char buffer[ALPHA_RELOC_DIGITS];
  struct alpha_reloc_tag *info;

  sprintf (buffer, "!%ld", sequence);

  info = (struct alpha_reloc_tag *) hash_find (alpha_literal_hash, buffer);
  if (! info)
    {
      size_t len = strlen (buffer);
      const char *errmsg;

      info = xcalloc (sizeof (struct alpha_reloc_tag) + len, 1);

      info->segment = now_seg;
      info->sequence = sequence;
      strcpy (info->string, buffer);
      errmsg = hash_insert (alpha_literal_hash, info->string, (void *) info);
      if (errmsg)
	as_fatal (errmsg);
    }

  return info;
}