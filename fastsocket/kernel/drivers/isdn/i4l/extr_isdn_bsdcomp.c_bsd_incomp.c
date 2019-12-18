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
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bsd_compress (void*,struct sk_buff*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void bsd_incomp (void *state, struct sk_buff *skb_in,int proto)
{
	bsd_compress (state, skb_in, NULL, proto);
}