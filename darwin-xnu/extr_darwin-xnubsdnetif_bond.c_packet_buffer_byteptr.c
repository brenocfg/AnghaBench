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
struct ether_header {int dummy; } ;
typedef  TYPE_1__* packet_buffer_ref ;
struct TYPE_3__ {void* m_data; } ;

/* Variables and functions */

__attribute__((used)) static void *
packet_buffer_byteptr(packet_buffer_ref buf)
{
    return (buf->m_data + sizeof(struct ether_header));
}