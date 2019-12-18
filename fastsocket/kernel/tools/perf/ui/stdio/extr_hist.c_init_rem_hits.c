#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* sym; } ;
struct TYPE_7__ {TYPE_1__ ms; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* malloc (int) ; 
 TYPE_3__ rem_hits ; 
 TYPE_2__* rem_sq_bracket ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void init_rem_hits(void)
{
	rem_sq_bracket = malloc(sizeof(*rem_sq_bracket) + 6);
	if (!rem_sq_bracket) {
		fprintf(stderr, "Not enough memory to display remaining hits\n");
		return;
	}

	strcpy(rem_sq_bracket->name, "[...]");
	rem_hits.ms.sym = rem_sq_bracket;
}