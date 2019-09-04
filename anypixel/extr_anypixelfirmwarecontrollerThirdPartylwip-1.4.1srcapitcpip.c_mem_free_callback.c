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
typedef  int /*<<< orphan*/  err_t ;

/* Variables and functions */
 int /*<<< orphan*/  mem_free ; 
 int /*<<< orphan*/  tcpip_callback_with_block (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

err_t
mem_free_callback(void *m)
{
  return tcpip_callback_with_block(mem_free, m, 0);
}