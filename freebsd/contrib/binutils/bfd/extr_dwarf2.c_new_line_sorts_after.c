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
struct line_info {scalar_t__ address; scalar_t__ end_sequence; } ;
typedef  int bfd_boolean ;

/* Variables and functions */

__attribute__((used)) static inline bfd_boolean
new_line_sorts_after (struct line_info *new_line, struct line_info *line)
{
  return (new_line->address > line->address
	  || (new_line->address == line->address
	      && new_line->end_sequence < line->end_sequence));
}