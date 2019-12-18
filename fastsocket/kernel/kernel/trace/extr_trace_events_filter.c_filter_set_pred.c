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
struct filter_pred {int /*<<< orphan*/  fn; scalar_t__ field_name; } ;
typedef  int /*<<< orphan*/  filter_pred_fn_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ kstrdup (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filter_set_pred(struct filter_pred *dest,
			   struct filter_pred *src,
			   filter_pred_fn_t fn)
{
	*dest = *src;
	if (src->field_name) {
		dest->field_name = kstrdup(src->field_name, GFP_KERNEL);
		if (!dest->field_name)
			return -ENOMEM;
	}
	dest->fn = fn;

	return 0;
}