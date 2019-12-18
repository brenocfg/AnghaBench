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
struct qstr {unsigned int len; char* name; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int vfat_striptail_len(struct qstr *qstr)
{
	unsigned int len = qstr->len;

	while (len && qstr->name[len - 1] == '.')
		len--;
	return len;
}