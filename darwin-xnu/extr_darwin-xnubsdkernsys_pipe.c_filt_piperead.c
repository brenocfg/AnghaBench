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
struct pipe {int dummy; } ;
struct knote {TYPE_1__* kn_fp; } ;
struct TYPE_2__ {scalar_t__ f_data; } ;

/* Variables and functions */
 int filt_piperead_common (struct knote*,struct pipe*) ; 

__attribute__((used)) static int
filt_piperead(struct knote *kn, long hint)
{
#pragma unused(hint)
	struct pipe *rpipe = (struct pipe *)kn->kn_fp->f_data;

	return filt_piperead_common(kn, rpipe);
}