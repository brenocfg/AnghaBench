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
struct trapsink {int socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct trapsink*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (struct trapsink*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  trapsink_list ; 

__attribute__((used)) static void
trapsink_free(struct trapsink *t)
{
	TAILQ_REMOVE(&trapsink_list, t, link);
	if (t->socket != -1)
		(void)close(t->socket);
	free(t);
}