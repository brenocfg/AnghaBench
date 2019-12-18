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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  hashnode ;

/* Variables and functions */
 int /*<<< orphan*/  HT_ALLOCED ; 
 int /*<<< orphan*/  HT_IDENT_TO_GCC_IDENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ht_lookup (int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ident_hash ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static inline tree
get_identifier_nocopy (const char *name)
{
  hashnode ht_node = ht_lookup (ident_hash, (const unsigned char *) name,
				strlen (name), HT_ALLOCED);
  return HT_IDENT_TO_GCC_IDENT (ht_node);
}