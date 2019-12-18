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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 scalar_t__ H_SUCCESS ; 
 scalar_t__ plpar_get_term_char (int /*<<< orphan*/ ,unsigned long*,char*) ; 

int hvc_get_chars(uint32_t vtermno, char *buf, int count)
{
	unsigned long got;

	if (plpar_get_term_char(vtermno, &got, buf) == H_SUCCESS)
		return got;

	return 0;
}