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
typedef  void nv04_vmmgr_priv ;

/* Variables and functions */
 scalar_t__ nouveau_vmmgr (void*) ; 

__attribute__((used)) static inline struct nv04_vmmgr_priv *
nv04_vmmgr(void *obj)
{
	return (void *)nouveau_vmmgr(obj);
}