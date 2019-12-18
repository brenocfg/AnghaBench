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
struct x509_name {size_t num_attr; int /*<<< orphan*/  email; TYPE_1__* attr; } ;
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int x509_str_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int x509_name_compare(struct x509_name *a, struct x509_name *b)
{
	int res;
	size_t i;

	if (!a && b)
		return -1;
	if (a && !b)
		return 1;
	if (!a && !b)
		return 0;
	if (a->num_attr < b->num_attr)
		return -1;
	if (a->num_attr > b->num_attr)
		return 1;

	for (i = 0; i < a->num_attr; i++) {
		if (a->attr[i].type < b->attr[i].type)
			return -1;
		if (a->attr[i].type > b->attr[i].type)
			return -1;
		res = x509_str_compare(a->attr[i].value, b->attr[i].value);
		if (res)
			return res;
	}
	res = x509_str_compare(a->email, b->email);
	if (res)
		return res;

	return 0;
}