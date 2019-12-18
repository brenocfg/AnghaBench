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
struct ipw_priv {int dummy; } ;

/* Variables and functions */
 int ipw_read32 (struct ipw_priv*,int) ; 

__attribute__((used)) static inline int ipw_alive(struct ipw_priv *priv)
{
	return ipw_read32(priv, 0x90) == 0xd55555d5;
}