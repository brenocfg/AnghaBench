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

/* Variables and functions */
 int /*<<< orphan*/  __dl_seterr (char*,void*) ; 

__attribute__((used)) static int stub_invalid_handle(void *h)
{
	__dl_seterr("Invalid library handle %p", (void *)h);
	return 1;
}