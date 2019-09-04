#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ubsan_violation {size_t ubsan_type; int /*<<< orphan*/  rhs; int /*<<< orphan*/  lhs; TYPE_1__* overflow; } ;
struct san_type_desc {char* name; int width; scalar_t__ issigned; } ;
struct TYPE_2__ {struct san_type_desc* ty; } ;

/* Variables and functions */
 char** overflow_str ; 
 size_t snprintf (char*,size_t,char*,char*,char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
format_overflow(struct ubsan_violation *v, char *buf, size_t sz)
{
	struct san_type_desc *ty = v->overflow->ty;
	return snprintf(buf, sz,
			"%s overflow, op = %s, ty = %s, width = %d, lhs = 0x%llx, rhs = 0x%llx\n",
			ty->issigned ? "signed" : "unsigned",
			overflow_str[v->ubsan_type],
			ty->name,
			1 << ty->width,
			v->lhs,
			v->rhs
		);
}