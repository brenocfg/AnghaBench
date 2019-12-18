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
 double GC_Load_Factor ; 
 size_t GC_PRIMES_COUNT ; 
 size_t* GC_Primes ; 

__attribute__((used)) static size_t GC_Ideal_Size(size_t size) {
  size = (size_t)((double)(size+1) / GC_Load_Factor);
  for (size_t i = 0; i < GC_PRIMES_COUNT; i++) {
    if (GC_Primes[i] >= size) { return GC_Primes[i]; }
  }
  size_t last = GC_Primes[GC_PRIMES_COUNT-1];
  for (size_t i = 0;; i++) {
    if (last * i >= size) { return last * i; }
  }
}