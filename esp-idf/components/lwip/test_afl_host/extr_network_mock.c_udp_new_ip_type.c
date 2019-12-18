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
typedef  int /*<<< orphan*/  u8_t ;
struct udp_pcb {int dummy; } ;

/* Variables and functions */
 struct udp_pcb mock_pcb ; 

struct udp_pcb * udp_new_ip_type(u8_t type)
{
    return &mock_pcb;
}