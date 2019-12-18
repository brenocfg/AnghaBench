#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned long* sig; } ;
typedef  TYPE_1__ sigset_t ;
struct TYPE_6__ {unsigned long* sig; } ;
typedef  TYPE_2__ compat_sigset_t ;

/* Variables and functions */

inline void
sigset_32to64(sigset_t *s64, compat_sigset_t *s32)
{
	s64->sig[0] = s32->sig[0] | ((unsigned long)s32->sig[1] << 32);
}