#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ len; scalar_t__ ptr; } ;
typedef  TYPE_1__ sb ;

/* Variables and functions */
 scalar_t__ do_scrub_chars (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sb_check (TYPE_1__*,scalar_t__) ; 
 TYPE_1__* sb_to_scrub ; 
 int /*<<< orphan*/  scrub_from_sb ; 
 scalar_t__ scrub_position ; 

void
sb_scrub_and_add_sb (sb *ptr, sb *s)
{
  sb_to_scrub = s;
  scrub_position = s->ptr;
  
  sb_check (ptr, s->len);
  ptr->len += do_scrub_chars (scrub_from_sb, ptr->ptr + ptr->len, s->len);

  sb_to_scrub = 0;
  scrub_position = 0;
}