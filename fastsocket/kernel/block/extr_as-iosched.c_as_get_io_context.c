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
struct io_context {scalar_t__ aic; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ alloc_as_io_context () ; 
 struct io_context* get_io_context (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_io_context (struct io_context*) ; 

__attribute__((used)) static struct io_context *as_get_io_context(int node)
{
	struct io_context *ioc = get_io_context(GFP_ATOMIC, node);
	if (ioc && !ioc->aic) {
		ioc->aic = alloc_as_io_context();
		if (!ioc->aic) {
			put_io_context(ioc);
			ioc = NULL;
		}
	}
	return ioc;
}