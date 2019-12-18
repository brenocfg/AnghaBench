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
typedef  scalar_t__ hashnode ;

/* Variables and functions */
 int /*<<< orphan*/  HT_IDENT_TO_GCC_IDENT (scalar_t__) ; 
 int /*<<< orphan*/  HT_NO_INSERT ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ ht_lookup (int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ident_hash ; 
 int /*<<< orphan*/  strlen (char const*) ; 

tree
maybe_get_identifier (const char *text)
{
  hashnode ht_node;

  ht_node = ht_lookup (ident_hash, (const unsigned char *) text,
		       strlen (text), HT_NO_INSERT);
  if (ht_node)
    return HT_IDENT_TO_GCC_IDENT (ht_node);

  return NULL_TREE;
}