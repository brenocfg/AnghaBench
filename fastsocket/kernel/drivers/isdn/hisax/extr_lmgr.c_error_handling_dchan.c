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
struct TYPE_2__ {int /*<<< orphan*/  (* l2tei ) (struct PStack*,int,int /*<<< orphan*/ *) ;} ;
struct PStack {TYPE_1__ l2; } ;

/* Variables and functions */
 int MDL_ERROR ; 
 int REQUEST ; 
 int /*<<< orphan*/  stub1 (struct PStack*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
error_handling_dchan(struct PStack *st, int Error)
{
	switch (Error) {
		case 'C':
		case 'D':
		case 'G':
		case 'H':
			st->l2.l2tei(st, MDL_ERROR | REQUEST, NULL);
			break;
	}
}