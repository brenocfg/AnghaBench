#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long hash; char const* string; struct bfd_hash_entry* next; } ;
struct sec_merge_hash_entry {unsigned int len; unsigned int alignment; TYPE_1__ root; } ;
struct TYPE_4__ {unsigned long size; struct bfd_hash_entry** table; } ;
struct sec_merge_hash {int entsize; TYPE_2__ table; scalar_t__ strings; } ;
struct bfd_hash_entry {int dummy; } ;
typedef  scalar_t__ bfd_boolean ;

/* Variables and functions */
 scalar_t__ memcmp (char const*,char const*,unsigned int) ; 
 scalar_t__ sec_merge_hash_newfunc (int /*<<< orphan*/ *,TYPE_2__*,char const*) ; 

__attribute__((used)) static struct sec_merge_hash_entry *
sec_merge_hash_lookup (struct sec_merge_hash *table, const char *string,
		       unsigned int alignment, bfd_boolean create)
{
  register const unsigned char *s;
  register unsigned long hash;
  register unsigned int c;
  struct sec_merge_hash_entry *hashp;
  unsigned int len, i;
  unsigned int index;

  hash = 0;
  len = 0;
  s = (const unsigned char *) string;
  if (table->strings)
    {
      if (table->entsize == 1)
	{
	  while ((c = *s++) != '\0')
	    {
	      hash += c + (c << 17);
	      hash ^= hash >> 2;
	      ++len;
	    }
	  hash += len + (len << 17);
	}
      else
	{
	  for (;;)
	    {
	      for (i = 0; i < table->entsize; ++i)
		if (s[i] != '\0')
		  break;
	      if (i == table->entsize)
		break;
	      for (i = 0; i < table->entsize; ++i)
		{
		  c = *s++;
		  hash += c + (c << 17);
		  hash ^= hash >> 2;
		}
	      ++len;
	    }
	  hash += len + (len << 17);
	  len *= table->entsize;
	}
      hash ^= hash >> 2;
      len += table->entsize;
    }
  else
    {
      for (i = 0; i < table->entsize; ++i)
	{
	  c = *s++;
	  hash += c + (c << 17);
	  hash ^= hash >> 2;
	}
      len = table->entsize;
    }

  index = hash % table->table.size;
  for (hashp = (struct sec_merge_hash_entry *) table->table.table[index];
       hashp != NULL;
       hashp = (struct sec_merge_hash_entry *) hashp->root.next)
    {
      if (hashp->root.hash == hash
	  && len == hashp->len
	  && memcmp (hashp->root.string, string, len) == 0)
	{
	  /* If the string we found does not have at least the required
	     alignment, we need to insert another copy.  */
	  if (hashp->alignment < alignment)
	    {
	      if (create)
		{
		  /*  Mark the less aligned copy as deleted.  */
		  hashp->len = 0;
		  hashp->alignment = 0;
		}
	      break;
	    }
	  return hashp;
	}
    }

  if (! create)
    return NULL;

  hashp = ((struct sec_merge_hash_entry *)
	   sec_merge_hash_newfunc (NULL, &table->table, string));
  if (hashp == NULL)
    return NULL;
  hashp->root.string = string;
  hashp->root.hash = hash;
  hashp->len = len;
  hashp->alignment = alignment;
  hashp->root.next = table->table.table[index];
  table->table.table[index] = (struct bfd_hash_entry *) hashp;

  return hashp;
}