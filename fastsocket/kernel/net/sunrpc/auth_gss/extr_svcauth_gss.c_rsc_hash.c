#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct rsc {TYPE_1__ handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSC_HASHBITS ; 
 int hash_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
rsc_hash(struct rsc *rsci)
{
	return hash_mem(rsci->handle.data, rsci->handle.len, RSC_HASHBITS);
}