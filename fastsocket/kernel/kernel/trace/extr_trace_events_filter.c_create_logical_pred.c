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
struct filter_pred {int op; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct filter_pred* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct filter_pred *create_logical_pred(int op)
{
	struct filter_pred *pred;

	pred = kzalloc(sizeof(*pred), GFP_KERNEL);
	if (!pred)
		return NULL;

	pred->op = op;

	return pred;
}