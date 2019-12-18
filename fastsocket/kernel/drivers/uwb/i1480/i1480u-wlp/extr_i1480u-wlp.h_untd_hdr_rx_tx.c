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
struct untd_hdr {int type; } ;

/* Variables and functions */

__attribute__((used)) static inline int untd_hdr_rx_tx(const struct untd_hdr *hdr)
{
	return (hdr->type >> 2) & 0x01;
}