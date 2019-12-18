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
struct TYPE_2__ {int /*<<< orphan*/  pattern; int /*<<< orphan*/  len; } ;
struct filter_pred {int op; TYPE_1__ regex; int /*<<< orphan*/  field_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct filter_pred*) ; 
 int /*<<< orphan*/  kstrdup (char*,int /*<<< orphan*/ ) ; 
 struct filter_pred* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct filter_pred *create_pred(int op, char *operand1, char *operand2)
{
	struct filter_pred *pred;

	pred = kzalloc(sizeof(*pred), GFP_KERNEL);
	if (!pred)
		return NULL;

	pred->field_name = kstrdup(operand1, GFP_KERNEL);
	if (!pred->field_name) {
		kfree(pred);
		return NULL;
	}

	strcpy(pred->regex.pattern, operand2);
	pred->regex.len = strlen(pred->regex.pattern);

	pred->op = op;

	return pred;
}