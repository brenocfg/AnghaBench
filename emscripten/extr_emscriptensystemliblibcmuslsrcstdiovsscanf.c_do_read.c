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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t __string_read (int /*<<< orphan*/ *,unsigned char*,size_t) ; 

__attribute__((used)) static size_t do_read(FILE *f, unsigned char *buf, size_t len)
{
	return __string_read(f, buf, len);
}