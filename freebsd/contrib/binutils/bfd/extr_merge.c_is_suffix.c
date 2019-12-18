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
struct TYPE_2__ {scalar_t__ string; } ;
struct sec_merge_hash_entry {scalar_t__ len; TYPE_1__ root; } ;

/* Variables and functions */
 scalar_t__ memcmp (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline int
is_suffix (const struct sec_merge_hash_entry *A,
	   const struct sec_merge_hash_entry *B)
{
  if (A->len <= B->len)
    /* B cannot be a suffix of A unless A is equal to B, which is guaranteed
       not to be equal by the hash table.  */
    return 0;

  return memcmp (A->root.string + (A->len - B->len),
		 B->root.string, B->len) == 0;
}