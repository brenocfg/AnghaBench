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
struct xt_u32 {int invert; } ;
struct xt_match_param {struct xt_u32* matchinfo; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int u32_match_it (struct xt_u32 const*,struct sk_buff const*) ; 

__attribute__((used)) static bool u32_mt(const struct sk_buff *skb, const struct xt_match_param *par)
{
	const struct xt_u32 *data = par->matchinfo;
	bool ret;

	ret = u32_match_it(data, skb);
	return ret ^ data->invert;
}