#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int len; int ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,int,int) ; 
 TYPE_1__* sb_to_scrub ; 
 int scrub_position ; 

__attribute__((used)) static int
scrub_from_sb (char *buf, int buflen)
{
  int copy;
  copy = sb_to_scrub->len - (scrub_position - sb_to_scrub->ptr);
  if (copy > buflen)
    copy = buflen;
  memcpy (buf, scrub_position, copy);
  scrub_position += copy;
  return copy;
}