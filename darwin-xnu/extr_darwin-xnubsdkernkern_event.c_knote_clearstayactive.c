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
struct knote {int /*<<< orphan*/  kn_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  KN_STAYACTIVE ; 
 int /*<<< orphan*/  knote_deactivate (struct knote*) ; 
 int /*<<< orphan*/  knote_get_kq (struct knote*) ; 
 int /*<<< orphan*/  kqlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kqunlock (int /*<<< orphan*/ ) ; 

void
knote_clearstayactive(struct knote *kn)
{
	kqlock(knote_get_kq(kn));
	kn->kn_status &= ~KN_STAYACTIVE;
	knote_deactivate(kn);
	kqunlock(knote_get_kq(kn));
}