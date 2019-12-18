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
typedef  scalar_t__ uint_t ;
struct TYPE_3__ {scalar_t__ ctb_base; scalar_t__ ctb_ptr; } ;
typedef  TYPE_1__ ctf_buf_t ;

/* Variables and functions */

__attribute__((used)) static uint_t
ctf_buf_cur(ctf_buf_t *b)
{
	return (b->ctb_ptr - b->ctb_base);
}