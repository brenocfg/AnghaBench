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
struct nstat_tucookie {int dummy; } ;
struct inpcb {int dummy; } ;

/* Variables and functions */
 struct nstat_tucookie* nstat_tucookie_alloc_internal (struct inpcb*,int,int) ; 

__attribute__((used)) static struct nstat_tucookie *
nstat_tucookie_alloc_ref(
    struct inpcb *inp)
{
	return nstat_tucookie_alloc_internal(inp, true, false);
}