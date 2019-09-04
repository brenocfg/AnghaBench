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
typedef  int u_int ;
struct recv_msg_elem {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 struct recv_msg_elem* _MALLOC (int,int /*<<< orphan*/ ,int) ; 

struct recv_msg_elem *
alloc_recv_msg_array(u_int count)
{
	struct recv_msg_elem *recv_msg_array;

	recv_msg_array = _MALLOC(count * sizeof(struct recv_msg_elem),
	    M_TEMP, M_WAITOK | M_ZERO);

	return (recv_msg_array);
}