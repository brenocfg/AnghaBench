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
typedef  int /*<<< orphan*/  QpelDSPContext ;

/* Variables and functions */

void ff_qpeldsp_init_mips(QpelDSPContext *c)
{
#if HAVE_MSA
    qpeldsp_init_msa(c);
#endif  // #if HAVE_MSA
}