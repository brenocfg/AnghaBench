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
struct hash_entry {unsigned long hash; char* string; struct hash_entry* next; } ;
struct hash_control {unsigned long size; int /*<<< orphan*/  string_compares; int /*<<< orphan*/  hash_compares; struct hash_entry** table; int /*<<< orphan*/  lookups; } ;

/* Variables and functions */
 scalar_t__ strncmp (char*,char const*,size_t) ; 

__attribute__((used)) static struct hash_entry *
hash_lookup (struct hash_control *table, const char *key, size_t len,
	     struct hash_entry ***plist, unsigned long *phash)
{
  unsigned long hash;
  size_t n;
  unsigned int c;
  unsigned int index;
  struct hash_entry **list;
  struct hash_entry *p;
  struct hash_entry *prev;

#ifdef HASH_STATISTICS
  ++table->lookups;
#endif

  hash = 0;
  for (n = 0; n < len; n++)
    {
      c = key[n];
      hash += c + (c << 17);
      hash ^= hash >> 2;
    }
  hash += len + (len << 17);
  hash ^= hash >> 2;

  if (phash != NULL)
    *phash = hash;

  index = hash % table->size;
  list = table->table + index;

  if (plist != NULL)
    *plist = list;

  prev = NULL;
  for (p = *list; p != NULL; p = p->next)
    {
#ifdef HASH_STATISTICS
      ++table->hash_compares;
#endif

      if (p->hash == hash)
	{
#ifdef HASH_STATISTICS
	  ++table->string_compares;
#endif

	  if (strncmp (p->string, key, len) == 0 && p->string[len] == '\0')
	    {
	      if (prev != NULL)
		{
		  prev->next = p->next;
		  p->next = *list;
		  *list = p;
		}

	      return p;
	    }
	}

      prev = p;
    }

  return NULL;
}