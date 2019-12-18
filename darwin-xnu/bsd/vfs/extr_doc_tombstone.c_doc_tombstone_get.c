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
struct uthread {struct doc_tombstone* t_tombstone; } ;
struct doc_tombstone {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_thread () ; 
 struct uthread* get_bsdthread_info (int /*<<< orphan*/ ) ; 
 struct doc_tombstone* kalloc (int) ; 
 int /*<<< orphan*/  memset (struct doc_tombstone*,int /*<<< orphan*/ ,int) ; 

struct doc_tombstone *
doc_tombstone_get(void)
{
	struct  uthread *ut;
	ut = get_bsdthread_info(current_thread());

	if (ut->t_tombstone == NULL) {
		ut->t_tombstone = kalloc(sizeof(struct doc_tombstone));
		if (ut->t_tombstone) {
			memset(ut->t_tombstone, 0, sizeof(struct doc_tombstone));
		}
	}

	return ut->t_tombstone;
}