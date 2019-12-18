#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hashval_t ;
struct TYPE_4__ {int /*<<< orphan*/ * bits; int /*<<< orphan*/  indx; struct TYPE_4__* next; } ;
typedef  TYPE_1__ bitmap_element ;
typedef  TYPE_2__* bitmap ;
struct TYPE_5__ {TYPE_1__* first; } ;
typedef  int /*<<< orphan*/  BITMAP_WORD ;

/* Variables and functions */
 int BITMAP_ELEMENT_WORDS ; 

hashval_t
bitmap_hash (bitmap head)
{
  bitmap_element *ptr;
  BITMAP_WORD hash = 0;
  int ix;

  for (ptr = head->first; ptr; ptr = ptr->next)
    {
      hash ^= ptr->indx;
      for (ix = 0; ix != BITMAP_ELEMENT_WORDS; ix++)
	hash ^= ptr->bits[ix];
    }
  return (hashval_t)hash;
}