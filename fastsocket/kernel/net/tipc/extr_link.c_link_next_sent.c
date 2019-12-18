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
typedef  int /*<<< orphan*/  u32 ;
struct link {int /*<<< orphan*/  next_out_no; scalar_t__ next_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  buf_msg (scalar_t__) ; 
 int /*<<< orphan*/  mod (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_seqno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 link_next_sent(struct link *l_ptr)
{
	if (l_ptr->next_out)
		return msg_seqno(buf_msg(l_ptr->next_out));
	return mod(l_ptr->next_out_no);
}