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
struct string {int len; int string; } ;
struct TYPE_2__ {int cols; int /*<<< orphan*/  dev; } ;
struct con3270 {TYPE_1__ view; } ;

/* Variables and functions */
 int /*<<< orphan*/  raw3270_buffer_address (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
con3270_update_string(struct con3270 *cp, struct string *s, int nr)
{
	if (s->len >= cp->view.cols - 5)
		return;
	raw3270_buffer_address(cp->view.dev, s->string + s->len - 3,
			       cp->view.cols * (nr + 1));
}