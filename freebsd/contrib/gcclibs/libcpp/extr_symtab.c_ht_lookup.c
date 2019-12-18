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
typedef  int /*<<< orphan*/  hashnode ;
typedef  int /*<<< orphan*/  hash_table ;
typedef  enum ht_lookup_option { ____Placeholder_ht_lookup_option } ht_lookup_option ;

/* Variables and functions */
 int /*<<< orphan*/  calc_hash (unsigned char const*,size_t) ; 
 int /*<<< orphan*/  ht_lookup_with_hash (int /*<<< orphan*/ *,unsigned char const*,size_t,int /*<<< orphan*/ ,int) ; 

hashnode
ht_lookup (hash_table *table, const unsigned char *str, size_t len,
	   enum ht_lookup_option insert)
{
  return ht_lookup_with_hash (table, str, len, calc_hash (str, len),
			      insert);
}