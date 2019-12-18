#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ len; scalar_t__ ptr; } ;
typedef  TYPE_1__ sb ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sb_check (TYPE_1__*,scalar_t__) ; 

void
sb_add_sb (sb *ptr, sb *s)
{
  sb_check (ptr, s->len);
  memcpy (ptr->ptr + ptr->len, s->ptr, s->len);
  ptr->len += s->len;
}