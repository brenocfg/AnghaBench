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
typedef  int /*<<< orphan*/  primes ;

/* Variables and functions */

__attribute__((used)) static unsigned long
higher_prime_number (unsigned long n)
{
  /* These are primes that are near, but slightly smaller than, a
     power of two.  */
  static const unsigned long primes[] = {
    (unsigned long) 127,
    (unsigned long) 2039,
    (unsigned long) 32749,
    (unsigned long) 65521,
    (unsigned long) 131071,
    (unsigned long) 262139,
    (unsigned long) 524287,
    (unsigned long) 1048573,
    (unsigned long) 2097143,
    (unsigned long) 4194301,
    (unsigned long) 8388593,
    (unsigned long) 16777213,
    (unsigned long) 33554393,
    (unsigned long) 67108859,
    (unsigned long) 134217689,
    (unsigned long) 268435399,
    (unsigned long) 536870909,
    (unsigned long) 1073741789,
    (unsigned long) 2147483647,
					/* 4294967291L */
    ((unsigned long) 2147483647) + ((unsigned long) 2147483644),
  };

  const unsigned long *low = &primes[0];
  const unsigned long *high = &primes[sizeof (primes) / sizeof (primes[0])];

  while (low != high)
    {
      const unsigned long *mid = low + (high - low) / 2;
      if (n >= *mid)
	low = mid + 1;
      else
	high = mid;
    }

  if (n >= *low)
    return 0;

  return *low;
}