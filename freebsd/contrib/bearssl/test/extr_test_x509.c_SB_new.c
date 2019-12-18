#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int len; scalar_t__ ptr; void* buf; } ;
typedef  TYPE_1__ string_builder ;

/* Variables and functions */
 void* xmalloc (int) ; 

__attribute__((used)) static string_builder *
SB_new(void)
{
	string_builder *sb;

	sb = xmalloc(sizeof *sb);
	sb->len = 8;
	sb->buf = xmalloc(sb->len);
	sb->ptr = 0;
	return sb;
}