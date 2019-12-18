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
struct TYPE_3__ {int /*<<< orphan*/  cb; } ;
typedef  TYPE_1__ cpp_reader ;
typedef  int /*<<< orphan*/  cpp_callbacks ;

/* Variables and functions */

void
cpp_set_callbacks (cpp_reader *pfile, cpp_callbacks *cb)
{
  pfile->cb = *cb;
}