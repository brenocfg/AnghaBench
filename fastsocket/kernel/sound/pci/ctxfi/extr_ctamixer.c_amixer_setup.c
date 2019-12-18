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
struct sum {int dummy; } ;
struct rsc {int dummy; } ;
struct amixer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  amixer_commit_write (struct amixer*) ; 
 int /*<<< orphan*/  amixer_set_input (struct amixer*,struct rsc*) ; 
 int /*<<< orphan*/  amixer_set_sum (struct amixer*,struct sum*) ; 
 int /*<<< orphan*/  amixer_set_y (struct amixer*,unsigned int) ; 

__attribute__((used)) static int amixer_setup(struct amixer *amixer, struct rsc *input,
			unsigned int scale, struct sum *sum)
{
	amixer_set_input(amixer, input);
	amixer_set_y(amixer, scale);
	amixer_set_sum(amixer, sum);
	amixer_commit_write(amixer);
	return 0;
}