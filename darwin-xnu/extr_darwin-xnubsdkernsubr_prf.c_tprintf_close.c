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
typedef  scalar_t__ tpr_t ;
struct session {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  session_rele (struct session*) ; 

void
tprintf_close(tpr_t sessp)
{
	if (sessp)
		session_rele((struct session *) sessp);
}