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
struct TYPE_2__ {scalar_t__ size; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 TYPE_1__ undo_load_buf ; 

bool content_undo_load_buf_is_empty(void)
{
   return undo_load_buf.data == NULL || undo_load_buf.size == 0;
}