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
struct pppol2tp_tunnel {int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pppol2tp_tunnel_free (struct pppol2tp_tunnel*) ; 

__attribute__((used)) static inline void pppol2tp_tunnel_dec_refcount(struct pppol2tp_tunnel *tunnel)
{
	if (atomic_dec_and_test(&tunnel->ref_count))
		pppol2tp_tunnel_free(tunnel);
}