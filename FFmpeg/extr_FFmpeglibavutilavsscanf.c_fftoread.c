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
struct TYPE_3__ {scalar_t__ buf_size; scalar_t__ buf; scalar_t__ rend; scalar_t__ rpos; } ;
typedef  TYPE_1__ FFFILE ;

/* Variables and functions */

__attribute__((used)) static int fftoread(FFFILE *f)
{
    f->rpos = f->rend = f->buf + f->buf_size;
    return 0;
}