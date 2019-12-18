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
struct ipw_priv {int status; } ;

/* Variables and functions */
 int STATUS_INIT ; 

__attribute__((used)) static inline int ipw_is_init(struct ipw_priv *priv)
{
	return (priv->status & STATUS_INIT) ? 1 : 0;
}