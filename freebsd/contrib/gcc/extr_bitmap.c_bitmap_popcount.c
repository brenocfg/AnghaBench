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
typedef  unsigned int BITMAP_WORD ;

/* Variables and functions */
 unsigned int BITMAP_WORD_BITS ; 
 scalar_t__* popcount_table ; 

__attribute__((used)) static unsigned long
bitmap_popcount (BITMAP_WORD a)
{
  unsigned long ret = 0;
  unsigned i;

  /* Just do this the table way for now  */
  for (i = 0; i < BITMAP_WORD_BITS; i+= 8)
    ret += popcount_table[(a >> i) & 0xff];
  return ret;
}