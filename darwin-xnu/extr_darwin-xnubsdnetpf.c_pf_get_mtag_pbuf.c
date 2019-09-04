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
struct pf_mtag {int dummy; } ;
typedef  int /*<<< orphan*/  pbuf_t ;

/* Variables and functions */
 struct pf_mtag* pf_find_mtag_pbuf (int /*<<< orphan*/ *) ; 

struct pf_mtag *
pf_get_mtag_pbuf(pbuf_t *pbuf)
{
	return (pf_find_mtag_pbuf(pbuf));
}