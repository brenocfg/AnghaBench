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
struct TYPE_3__ {scalar_t__ rend; scalar_t__ rpos; scalar_t__ wend; scalar_t__ wbase; scalar_t__ wpos; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */

int __fpurge(FILE *f)
{
	f->wpos = f->wbase = f->wend = 0;
	f->rpos = f->rend = 0;
	return 0;
}