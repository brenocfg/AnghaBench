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
struct TYPE_4__ {size_t ptr; scalar_t__ buf; } ;
typedef  TYPE_1__ string_builder ;

/* Variables and functions */
 int /*<<< orphan*/  SB_expand (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  memset (scalar_t__,char,size_t) ; 

__attribute__((used)) static void
SB_set_length(string_builder *sb, size_t len)
{
	if (sb->ptr < len) {
		SB_expand(sb, len - sb->ptr);
		memset(sb->buf + sb->ptr, ' ', len - sb->ptr);
	}
	sb->ptr = len;
}