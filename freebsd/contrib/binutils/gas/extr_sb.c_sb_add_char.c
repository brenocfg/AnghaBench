#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* ptr; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ sb ;

/* Variables and functions */
 int /*<<< orphan*/  sb_check (TYPE_1__*,int) ; 

void
sb_add_char (sb *ptr, int c)
{
  sb_check (ptr, 1);
  ptr->ptr[ptr->len++] = c;
}