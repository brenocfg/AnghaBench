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
 int /*<<< orphan*/  TOMOYO_ROOT_NAME ; 
 int /*<<< orphan*/  TOMOYO_ROOT_NAME_LEN ; 
 int /*<<< orphan*/  strncmp (unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool tomoyo_is_domain_def(const unsigned char *buffer)
{
	return !strncmp(buffer, TOMOYO_ROOT_NAME, TOMOYO_ROOT_NAME_LEN);
}