#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mbuf_t ;
struct TYPE_4__ {int m_flags; } ;

/* Variables and functions */
 int M_EXT ; 
 int m_mclhasreference (TYPE_1__*) ; 

int
mbuf_mclhasreference(mbuf_t mbuf)
{
	if ((mbuf->m_flags & M_EXT))
		return (m_mclhasreference(mbuf));
	else
		return (0);
}