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
typedef  int /*<<< orphan*/  mbstate_t ;
typedef  int /*<<< orphan*/  char32_t ;

/* Variables and functions */
 size_t wcrtomb (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

size_t c32rtomb(char *restrict s, char32_t c32, mbstate_t *restrict ps)
{
	return wcrtomb(s, c32, ps);
}