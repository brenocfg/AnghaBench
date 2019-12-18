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
struct napi_struct {int dummy; } ;
typedef  int /*<<< orphan*/  gro_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  __napi_gro_receive (struct napi_struct*,struct sk_buff*) ; 
 int /*<<< orphan*/  napi_skb_finish (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_gro_reset_offset (struct sk_buff*) ; 

__attribute__((used)) static inline gro_result_t __napi_gro_receive_gr(struct napi_struct *napi,
						 struct sk_buff *skb)
{
	skb_gro_reset_offset(skb);

	return napi_skb_finish(__napi_gro_receive(napi, skb), skb);
}