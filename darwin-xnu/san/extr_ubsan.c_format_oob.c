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
struct ubsan_violation {uintptr_t lhs; TYPE_1__* oob; } ;
struct san_type_desc {char* name; int issigned; int width; } ;
struct TYPE_2__ {struct san_type_desc* index_ty; struct san_type_desc* array_ty; } ;

/* Variables and functions */
 scalar_t__ snprintf (char*,size_t,char*,...) ; 

__attribute__((used)) static size_t
format_oob(struct ubsan_violation *v, char *buf, size_t sz)
{
	size_t n = 0;
	struct san_type_desc *aty = v->oob->array_ty;
	struct san_type_desc *ity = v->oob->index_ty;
	uintptr_t idx = v->lhs;

	n += snprintf(buf+n, sz-n, "OOB array access\n");
	n += snprintf(buf+n, sz-n, "  idx %ld\n", idx);
	n += snprintf(buf+n, sz-n, "  aty: ty = %s, signed = %d, width = %d\n", aty->name, aty->issigned, 1 << aty->width);
	n += snprintf(buf+n, sz-n, "  ity: ty = %s, signed = %d, width = %d\n", ity->name, ity->issigned, 1 << ity->width);

	return n;
}