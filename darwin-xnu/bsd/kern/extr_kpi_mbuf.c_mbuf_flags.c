#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mbuf_t ;
typedef  int mbuf_flags_t ;
struct TYPE_3__ {int m_flags; } ;

/* Variables and functions */
 int mbuf_flags_mask ; 

mbuf_flags_t
mbuf_flags(const mbuf_t mbuf)
{
	return (mbuf->m_flags & mbuf_flags_mask);
}