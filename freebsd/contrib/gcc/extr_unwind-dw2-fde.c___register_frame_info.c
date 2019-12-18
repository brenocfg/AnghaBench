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
struct object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __register_frame_info_bases (void const*,struct object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
__register_frame_info (const void *begin, struct object *ob)
{
  __register_frame_info_bases (begin, ob, 0, 0);
}