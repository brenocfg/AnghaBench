#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* buf; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ string_builder ;

/* Variables and functions */
 int /*<<< orphan*/  SB_expand (TYPE_1__*,int) ; 

__attribute__((used)) static void
SB_append_char(string_builder *sb, int c)
{
	SB_expand(sb, 1);
	sb->buf[sb->ptr ++] = c;
}