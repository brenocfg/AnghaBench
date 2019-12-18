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

/* Variables and functions */
 int _content_is_inited ; 
 int core_does_not_need_content ; 

void content_get_status(
      bool *contentless,
      bool *is_inited)
{
   *contentless = core_does_not_need_content;
   *is_inited   = _content_is_inited;
}