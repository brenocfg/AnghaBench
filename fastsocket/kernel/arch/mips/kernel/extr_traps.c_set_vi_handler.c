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
typedef  int /*<<< orphan*/  vi_handler_t ;

/* Variables and functions */
 void* set_vi_srs_handler (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void *set_vi_handler(int n, vi_handler_t addr)
{
	return set_vi_srs_handler(n, addr, 0);
}