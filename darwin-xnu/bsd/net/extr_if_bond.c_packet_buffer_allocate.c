#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ether_header {int dummy; } ;
typedef  TYPE_2__* packet_buffer_ref ;
struct TYPE_6__ {int len; } ;
struct TYPE_7__ {int m_len; TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int MCLBYTES ; 
 scalar_t__ MHLEN ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 int /*<<< orphan*/  M_WAITOK ; 
 TYPE_2__* m_getcl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* m_gethdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static packet_buffer_ref
packet_buffer_allocate(int length)
{
    packet_buffer_ref	m;
    int			size;

    /* leave room for ethernet header */
    size = length + sizeof(struct ether_header);
    if (size > (int)MHLEN) {
	if (size > (int)MCLBYTES) {
	    printf("bond: packet_buffer_allocate size %d > max %u\n",
	           size, MCLBYTES);
	    return (NULL);
	}
	m = m_getcl(M_WAITOK, MT_DATA, M_PKTHDR);
    } else {
	m = m_gethdr(M_WAITOK, MT_DATA);
    }
    if (m == NULL) {
	return (NULL);
    }
    m->m_len = size;
    m->m_pkthdr.len = size;
    return (m);
}