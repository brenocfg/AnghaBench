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
struct TYPE_2__ {char const* str; } ;
struct attr_hash {int hashcode; TYPE_1__ u; struct attr_hash* next; } ;

/* Variables and functions */
 int RTL_HASH_SIZE ; 
 int /*<<< orphan*/  attr_hash_add_string (int,char*) ; 
 struct attr_hash** attr_hash_table ; 
 int /*<<< orphan*/  hash_obstack ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* obstack_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,int) ; 

__attribute__((used)) static char *
attr_string (const char *str, int len)
{
  struct attr_hash *h;
  int hashcode;
  int i;
  char *new_str;

  /* Compute the hash code.  */
  hashcode = (len + 1) * 613 + (unsigned) str[0];
  for (i = 1; i < len; i += 2)
    hashcode = ((hashcode * 613) + (unsigned) str[i]);
  if (hashcode < 0)
    hashcode = -hashcode;

  /* Search the table for the string.  */
  for (h = attr_hash_table[hashcode % RTL_HASH_SIZE]; h; h = h->next)
    if (h->hashcode == -hashcode && h->u.str[0] == str[0]
	&& !strncmp (h->u.str, str, len))
      return h->u.str;			/* <-- return if found.  */

  /* Not found; create a permanent copy and add it to the hash table.  */
  new_str = obstack_alloc (hash_obstack, len + 1);
  memcpy (new_str, str, len);
  new_str[len] = '\0';
  attr_hash_add_string (hashcode, new_str);

  return new_str;			/* Return the new string.  */
}