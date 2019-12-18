#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int (* aid_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  aid_priv; } ;
typedef  TYPE_1__ alist_iter_data_t ;
struct TYPE_4__ {int /*<<< orphan*/  ale_value; int /*<<< orphan*/  ale_name; } ;
typedef  TYPE_2__ alist_el_t ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
alist_iter_cb(void *arg1, void *arg2)
{
	alist_el_t *el = arg1;
	alist_iter_data_t *aid = arg2;
	return (aid->aid_func(el->ale_name, el->ale_value, aid->aid_priv));
}