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
struct napi_struct {int dummy; } ;

/* Variables and functions */
 scalar_t__ GRO_DROP ; 
 int NET_RX_DROP ; 
 int NET_RX_SUCCESS ; 
 scalar_t__ __napi_gro_frags_gr (struct napi_struct*) ; 

int napi_gro_frags(struct napi_struct *napi)
{
	return __napi_gro_frags_gr(napi) == GRO_DROP
		? NET_RX_DROP : NET_RX_SUCCESS;
}