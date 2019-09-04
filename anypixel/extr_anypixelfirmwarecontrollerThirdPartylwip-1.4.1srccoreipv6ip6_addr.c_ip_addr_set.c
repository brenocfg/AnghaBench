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
struct ip_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMEMCPY (struct ip_addr*,struct ip_addr*,int) ; 

void
ip_addr_set(struct ip_addr *dest, struct ip_addr *src)
{
  SMEMCPY(dest, src, sizeof(struct ip_addr));
  /*  dest->addr[0] = src->addr[0];
  dest->addr[1] = src->addr[1];
  dest->addr[2] = src->addr[2];
  dest->addr[3] = src->addr[3];*/
}