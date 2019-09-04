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
struct nd6_prproxy_prelist {int dummy; } ;

/* Variables and functions */
 int M_WAITOK ; 
 int /*<<< orphan*/  bzero (struct nd6_prproxy_prelist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ndprl_size ; 
 int /*<<< orphan*/  ndprl_zone ; 
 struct nd6_prproxy_prelist* zalloc (int /*<<< orphan*/ ) ; 
 struct nd6_prproxy_prelist* zalloc_noblock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nd6_prproxy_prelist *
nd6_ndprl_alloc(int how)
{
	struct nd6_prproxy_prelist *ndprl;

	ndprl = (how == M_WAITOK) ? zalloc(ndprl_zone) :
	    zalloc_noblock(ndprl_zone);
	if (ndprl != NULL)
		bzero(ndprl, ndprl_size);

	return (ndprl);
}