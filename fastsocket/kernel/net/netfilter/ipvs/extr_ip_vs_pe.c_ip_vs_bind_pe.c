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
struct ip_vs_service {struct ip_vs_pe* pe; } ;
struct ip_vs_pe {int dummy; } ;

/* Variables and functions */

void ip_vs_bind_pe(struct ip_vs_service *svc, struct ip_vs_pe *pe)
{
	svc->pe = pe;
}