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
struct ubsan_violation {TYPE_1__* align; int /*<<< orphan*/  lhs; } ;
struct san_type_desc {char* name; } ;
struct TYPE_2__ {size_t kind; int align; struct san_type_desc* ty; } ;

/* Variables and functions */
 char** align_kinds ; 
 scalar_t__ snprintf (char*,size_t,char*,...) ; 

__attribute__((used)) static size_t
format_alignment(struct ubsan_violation *v, char *buf, size_t sz)
{
	size_t n = 0;
	struct san_type_desc *ty = v->align->ty;

	n += snprintf(buf+n, sz-n, "mis-aligned %s of 0x%llx\n", align_kinds[v->align->kind], v->lhs);
	n += snprintf(buf+n, sz-n, "  expected %d-byte alignment, type = %s\n",
			1 << v->align->align, ty->name);
	return n;
}