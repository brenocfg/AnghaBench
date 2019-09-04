#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* mbuf_t ;
struct TYPE_5__ {size_t ext_size; } ;
struct TYPE_6__ {int m_flags; char* m_dat; TYPE_1__ m_ext; } ;

/* Variables and functions */
 size_t MLEN ; 
 int M_EXT ; 
 scalar_t__ mbuf_datastart (TYPE_2__* const) ; 

size_t
mbuf_maxlen(const mbuf_t mbuf)
{
	if (mbuf->m_flags & M_EXT)
		return (mbuf->m_ext.ext_size);
	return (&mbuf->m_dat[MLEN] - ((char *)mbuf_datastart(mbuf)));
}