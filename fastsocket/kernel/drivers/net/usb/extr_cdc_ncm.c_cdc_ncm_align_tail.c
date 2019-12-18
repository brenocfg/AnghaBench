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
struct sk_buff {size_t len; } ;

/* Variables and functions */
 size_t ALIGN (size_t,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,size_t) ; 
 size_t skb_tailroom (struct sk_buff*) ; 

__attribute__((used)) static void cdc_ncm_align_tail(struct sk_buff *skb, size_t modulus, size_t remainder, size_t max)
{
	size_t align = ALIGN(skb->len, modulus) - skb->len + remainder;

	if (skb->len + align > max)
		align = max - skb->len;
	if (align && skb_tailroom(skb) >= align)
		memset(skb_put(skb, align), 0, align);
}