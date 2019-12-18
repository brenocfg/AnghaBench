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
struct TYPE_2__ {int /*<<< orphan*/  category; } ;
typedef  int /*<<< orphan*/  AVClassCategory ;
typedef  TYPE_1__ AVClass ;

/* Variables and functions */

AVClassCategory av_default_get_category(void *ptr)
{
    return (*(AVClass **) ptr)->category;
}