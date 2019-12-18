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
typedef  int /*<<< orphan*/  vm_map_size_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  ledger_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  PMAP_CREATE_64BIT ; 
 int /*<<< orphan*/  pmap_create_options (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

pmap_t
pmap_create(
	ledger_t	ledger,
	vm_map_size_t	sz,
	boolean_t	is_64bit)
{
	return pmap_create_options(ledger, sz, ((is_64bit) ? PMAP_CREATE_64BIT : 0));
}