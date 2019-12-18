#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ptr; int base; int limit; } ;
typedef  TYPE_1__ sstring ;

/* Variables and functions */
 int xrealloc (int,int) ; 

void
make_sstring_space (sstring *str, int count)
{
  int cur_pos = str->ptr - str->base;
  int cur_size = str->limit - str->base;
  int new_size = cur_pos + count + 100;

  if (new_size <= cur_size)
    return;

  str->base = xrealloc (str->base, new_size);
  str->ptr = str->base + cur_size;
  str->limit = str->base + new_size;
}