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
struct knote {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct knote*,int) ; 
 int /*<<< orphan*/  knote_zone ; 
 scalar_t__ zalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct knote *
knote_alloc(void)
{
	struct knote *kn = ((struct knote *)zalloc(knote_zone));
	bzero(kn, sizeof(struct knote));
	return kn;
}