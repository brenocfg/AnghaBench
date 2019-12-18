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
typedef  int /*<<< orphan*/  symbolS ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_fatal (int /*<<< orphan*/ ,char const*,char const*) ; 
 char* hash_jam (int /*<<< orphan*/ ,char const*,char*) ; 
 int /*<<< orphan*/  tag_hash ; 

__attribute__((used)) static void
tag_insert (const char *name, symbolS *symbolP)
{
  const char *error_string;

  if ((error_string = hash_jam (tag_hash, name, (char *) symbolP)))
    as_fatal (_("Inserting \"%s\" into structure table failed: %s"),
	      name, error_string);
}