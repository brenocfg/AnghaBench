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
 int /*<<< orphan*/  __dl_seterr (char*) ; 

__attribute__((used)) static void *stub_dlopen(const char *file, int mode)
{
	__dl_seterr("Dynamic loading not supported");
	return 0;
}