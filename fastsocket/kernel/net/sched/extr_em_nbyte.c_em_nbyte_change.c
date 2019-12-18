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
struct tcf_proto {int dummy; } ;
struct tcf_ematch {int datalen; unsigned long data; } ;
struct tcf_em_nbyte {int len; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ kmemdup (void*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int em_nbyte_change(struct tcf_proto *tp, void *data, int data_len,
			   struct tcf_ematch *em)
{
	struct tcf_em_nbyte *nbyte = data;

	if (data_len < sizeof(*nbyte) ||
	    data_len < (sizeof(*nbyte) + nbyte->len))
		return -EINVAL;

	em->datalen = sizeof(*nbyte) + nbyte->len;
	em->data = (unsigned long)kmemdup(data, em->datalen, GFP_KERNEL);
	if (em->data == 0UL)
		return -ENOBUFS;

	return 0;
}