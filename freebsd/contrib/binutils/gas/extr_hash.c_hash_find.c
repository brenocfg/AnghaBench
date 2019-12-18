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
struct hash_entry {int /*<<< orphan*/ * data; } ;
struct hash_control {int dummy; } ;
typedef  int /*<<< orphan*/ * PTR ;

/* Variables and functions */
 struct hash_entry* hash_lookup (struct hash_control*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

PTR
hash_find (struct hash_control *table, const char *key)
{
  struct hash_entry *p;

  p = hash_lookup (table, key, strlen (key), NULL, NULL);
  if (p == NULL)
    return NULL;

  return p->data;
}