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
typedef  int /*<<< orphan*/  UNSIGNED_INTEGER ;

/* Variables and functions */
 scalar_t__ STRTOUI (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static UNSIGNED_INTEGER
my_custom_atoui(const char * s)
{
	return s ? ((UNSIGNED_INTEGER)STRTOUI(s, NULL, 0)) : 0;
}