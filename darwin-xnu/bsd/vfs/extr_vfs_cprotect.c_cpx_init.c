#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* cpx_t ;
struct TYPE_4__ {size_t cpx_max_key_len; scalar_t__ cpx_key_len; scalar_t__ cpx_flags; int /*<<< orphan*/  cpx_magic1; } ;

/* Variables and functions */
 int /*<<< orphan*/ * PTR_ADD (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  cpx_magic1 ; 
 int /*<<< orphan*/  cpx_magic2 ; 
 scalar_t__ cpx_size (size_t) ; 
 int /*<<< orphan*/  uint32_t ; 

void cpx_init(cpx_t cpx, size_t key_len)
{
#if DEBUG
	cpx->cpx_magic1 = cpx_magic1;
	*PTR_ADD(uint32_t *, cpx, cpx_size(key_len) - 4) = cpx_magic2;
#endif
	cpx->cpx_flags = 0;
	cpx->cpx_key_len = 0;
	cpx->cpx_max_key_len = key_len;
}