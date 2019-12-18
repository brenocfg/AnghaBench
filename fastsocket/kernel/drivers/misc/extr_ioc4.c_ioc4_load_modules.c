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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct work_struct*) ; 
 int /*<<< orphan*/  request_module (char*) ; 

__attribute__((used)) static void
ioc4_load_modules(struct work_struct *work)
{
	/* arg just has to be freed */

	request_module("sgiioc4");

	kfree(work);
}