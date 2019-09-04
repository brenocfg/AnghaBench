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
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_UP ; 
 int gif_remove (struct ifnet*) ; 
 int ifnet_detach (struct ifnet*) ; 
 int ifnet_set_flags (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,struct ifnet*,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
gif_clone_destroy(struct ifnet *ifp)
{
	int error = 0;

	error = gif_remove(ifp);
	if (error != 0) {
		printf("gif_clone_destroy: gif remove failed %d\n", error);
		return (error);
	}

	error = ifnet_set_flags(ifp, 0, IFF_UP);
	if (error != 0) {
		printf("gif_clone_destroy: ifnet_set_flags failed %d\n", error);
	}

	error = ifnet_detach(ifp);
	if (error != 0)
		panic("gif_clone_destroy: ifnet_detach(%p) failed %d\n", ifp,
		    error);
	return (0);
}