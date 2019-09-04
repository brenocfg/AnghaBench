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
 int ifnet_detach (struct ifnet*) ; 
 char* ifnet_name (struct ifnet*) ; 
 int ifnet_unit (struct ifnet*) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int) ; 

__attribute__((used)) static void
bond_if_detach(struct ifnet * ifp)
{
    int		error;

    error = ifnet_detach(ifp);
    if (error) {
	printf("bond_if_detach %s%d: ifnet_detach failed, %d\n",
	       ifnet_name(ifp), ifnet_unit(ifp), error);
    }
	
    return;
}