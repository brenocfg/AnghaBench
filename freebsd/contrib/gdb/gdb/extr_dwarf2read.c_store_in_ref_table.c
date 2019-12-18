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
struct die_info {struct die_info* next_ref; } ;

/* Variables and functions */
 unsigned int REF_HASH_SIZE ; 
 struct die_info** die_ref_table ; 

__attribute__((used)) static void
store_in_ref_table (unsigned int offset, struct die_info *die)
{
  int h;
  struct die_info *old;

  h = (offset % REF_HASH_SIZE);
  old = die_ref_table[h];
  die->next_ref = old;
  die_ref_table[h] = die;
}