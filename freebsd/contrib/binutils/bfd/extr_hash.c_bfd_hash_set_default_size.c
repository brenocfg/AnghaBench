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
typedef  int bfd_size_type ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int bfd_default_hash_table_size ; 

void
bfd_hash_set_default_size (bfd_size_type hash_size)
{
  /* Extend this prime list if you want more granularity of hash table size.  */
  static const bfd_size_type hash_size_primes[] =
    {
      251, 509, 1021, 2039, 4051, 8599, 16699, 32749
    };
  size_t index;

  /* Work out best prime number near the hash_size.  */
  for (index = 0; index < ARRAY_SIZE (hash_size_primes) - 1; ++index)
    if (hash_size <= hash_size_primes[index])
      break;

  bfd_default_hash_table_size = hash_size_primes[index];
}