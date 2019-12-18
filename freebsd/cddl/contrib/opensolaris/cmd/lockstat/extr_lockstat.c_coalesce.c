#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__* ls_hist; scalar_t__ ls_time; scalar_t__ ls_refcnt; scalar_t__ ls_count; int /*<<< orphan*/  ls_event; } ;
typedef  TYPE_1__ lsrec_t ;

/* Variables and functions */
 scalar_t__ LS_HIST ; 
 int /*<<< orphan*/  LS_MAX_EVENTS ; 
 scalar_t__ LS_TIME ; 
 scalar_t__ g_recsize ; 

__attribute__((used)) static void
coalesce(int (*cmp)(lsrec_t *, lsrec_t *), lsrec_t **lock, int n)
{
	int i, j;
	lsrec_t *target, *current;

	target = lock[0];

	for (i = 1; i < n; i++) {
		current = lock[i];
		if (cmp(current, target) != 0) {
			target = current;
			continue;
		}
		current->ls_event = LS_MAX_EVENTS;
		target->ls_count += current->ls_count;
		target->ls_refcnt += current->ls_refcnt;
		if (g_recsize < LS_TIME)
			continue;
		target->ls_time += current->ls_time;
		if (g_recsize < LS_HIST)
			continue;
		for (j = 0; j < 64; j++)
			target->ls_hist[j] += current->ls_hist[j];
	}
}