#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  str; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ GString ;

/* Variables and functions */
 int /*<<< orphan*/  g_string_assign (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* g_string_sized_new (int /*<<< orphan*/ ) ; 

GString *g_string_dup(GString *src) {
	GString *dst = g_string_sized_new(src->len);

	g_string_assign(dst, src->str);

	return dst;
}