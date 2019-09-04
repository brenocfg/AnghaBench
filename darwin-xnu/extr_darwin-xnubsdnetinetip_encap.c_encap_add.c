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
struct encaptab {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct encaptab*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chain ; 
 int /*<<< orphan*/  encaptab ; 

__attribute__((used)) static void
encap_add(struct encaptab *ep)
{
	LIST_INSERT_HEAD(&encaptab, ep, chain);
}