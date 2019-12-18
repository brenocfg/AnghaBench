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
struct reg_entry {int /*<<< orphan*/  name; } ;
struct hash_control {int dummy; } ;

/* Variables and functions */
 char TOUPPER (char) ; 
 int /*<<< orphan*/  hash_insert (struct hash_control*,char*,void*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 char* xmalloc (int) ; 

__attribute__((used)) static void
insert_reg (const struct reg_entry *r, struct hash_control *htab)
{
  int i = 0;
  int len = strlen (r->name) + 2;
  char *buf = xmalloc (len);
  char *buf2 = xmalloc (len);

  strcpy (buf + i, r->name);
  for (i = 0; buf[i]; i++)
    {
      buf2[i] = TOUPPER (buf[i]);
    }
  buf2[i] = '\0';

  hash_insert (htab, buf, (void *) r);
  hash_insert (htab, buf2, (void *) r);
}