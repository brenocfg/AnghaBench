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
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  READ ; 
 int submit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bio**) ; 
 int /*<<< orphan*/  virt_to_page (void*) ; 

__attribute__((used)) static int bio_read_page(pgoff_t page_off, void *addr, struct bio **bio_chain)
{
	return submit(READ, page_off, virt_to_page(addr), bio_chain);
}