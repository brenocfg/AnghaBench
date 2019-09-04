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
struct route {int dummy; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  ro ;

/* Variables and functions */
 int /*<<< orphan*/  ROUTE_RELEASE (struct route*) ; 
 int /*<<< orphan*/  bzero (struct route*,int) ; 
 int ip_output (struct mbuf*,int /*<<< orphan*/ *,struct route*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
ip_gre_output(struct mbuf *m)
{
	struct route ro;
	int error;

	bzero(&ro, sizeof (ro));

	error = ip_output(m, NULL, &ro, 0, NULL, NULL);

	ROUTE_RELEASE(&ro);

	return (error);
}