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
struct slic_cmdqmem {int dummy; } ;
struct adapter {struct slic_cmdqmem cmdqmem; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct slic_cmdqmem*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void slic_cmdqmem_init(struct adapter *adapter)
{
	struct slic_cmdqmem *cmdqmem = &adapter->cmdqmem;

	memset(cmdqmem, 0, sizeof(struct slic_cmdqmem));
}