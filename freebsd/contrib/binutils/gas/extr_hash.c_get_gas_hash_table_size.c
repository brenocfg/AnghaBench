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

/* Variables and functions */
 int ARRAY_SIZE (unsigned long const*) ; 
 unsigned long const gas_hash_table_size ; 

__attribute__((used)) static unsigned long
get_gas_hash_table_size (void)
{
  /* Extend this prime list if you want more granularity of hash table size.  */
  static const unsigned long hash_size_primes[] =
    {
      1021, 4051, 8599, 16699, 65537
    };
  unsigned int index;

  /* Work out the best prime number near the hash_size.
     FIXME: This could be a more sophisticated algorithm,
     but is it really worth implementing it ?   */
  for (index = 0; index < ARRAY_SIZE (hash_size_primes) - 1; ++index)
    if (gas_hash_table_size <= hash_size_primes[index])
      break;

  return hash_size_primes[index];
}