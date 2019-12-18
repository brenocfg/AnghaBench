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
struct rsc {int dummy; } ;
struct amixer {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* commit_write ) (struct amixer*) ;int /*<<< orphan*/  (* set_input ) (struct amixer*,struct rsc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct amixer*,struct rsc*) ; 
 int /*<<< orphan*/  stub2 (struct amixer*) ; 

__attribute__((used)) static int mixer_set_input_port(struct amixer *amixer, struct rsc *rsc)
{
	amixer->ops->set_input(amixer, rsc);
	amixer->ops->commit_write(amixer);

	return 0;
}