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
struct sk_buff_head {int dummy; } ;
struct pfifo_fast_priv {struct sk_buff_head* q; } ;

/* Variables and functions */

__attribute__((used)) static inline struct sk_buff_head *band2list(struct pfifo_fast_priv *priv,
					     int band)
{
	return priv->q + band;
}