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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct ether_header {int ether_type; int /*<<< orphan*/ * ether_dhost; } ;

/* Variables and functions */

__attribute__((used)) static uint32_t
ether_header_hash(struct ether_header * eh_p)
{
    uint32_t	h;

    /* get 32-bits from destination ether and ether type */
    h = (*((uint16_t *)&eh_p->ether_dhost[4]) << 16)
	| eh_p->ether_type;
    h ^= *((uint32_t *)&eh_p->ether_dhost[0]);
    return (h);
}