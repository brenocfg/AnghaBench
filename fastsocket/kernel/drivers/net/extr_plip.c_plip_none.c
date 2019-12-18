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
struct plip_local {int dummy; } ;
struct net_local {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int OK ; 

__attribute__((used)) static int
plip_none(struct net_device *dev, struct net_local *nl,
	  struct plip_local *snd, struct plip_local *rcv)
{
	return OK;
}