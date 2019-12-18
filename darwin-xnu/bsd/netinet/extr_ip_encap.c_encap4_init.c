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
struct protosw {int dummy; } ;
struct domain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  encap_init (struct protosw*,struct domain*) ; 

void
encap4_init(struct protosw *pp, struct domain *dp)
{
	encap_init(pp, dp);
}