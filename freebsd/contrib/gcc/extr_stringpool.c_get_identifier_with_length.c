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
 int /*<<< orphan*/  HT_ALLOC ; 
 int /*<<< orphan*/  HT_IDENT_TO_GCC_IDENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ht_lookup (int /*<<< orphan*/ ,unsigned char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ident_hash ; 

tree
get_identifier_with_length (const char *text, size_t length)
{
  hashnode ht_node = ht_lookup (ident_hash,
				(const unsigned char *) text,
				length, HT_ALLOC);

  /* ht_node can't be NULL here.  */
  return HT_IDENT_TO_GCC_IDENT (ht_node);
}