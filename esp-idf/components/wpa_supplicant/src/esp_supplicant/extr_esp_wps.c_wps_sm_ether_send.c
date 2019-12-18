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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct wps_sm {int /*<<< orphan*/  const* ownaddr; } ;
struct l2_ethhdr {int /*<<< orphan*/  h_proto; int /*<<< orphan*/  h_source; int /*<<< orphan*/  h_dest; } ;

/* Variables and functions */
 int ESP_OK ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  host_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wps_sendto_wrapper (void*,int) ; 

__attribute__((used)) static inline int wps_sm_ether_send(struct wps_sm *sm, const u8 *dest, u16 proto,
                                    const u8 *data, size_t data_len)
{
    void *buffer = (void *)(data - sizeof(struct l2_ethhdr));
    struct l2_ethhdr *eth = (struct l2_ethhdr *)buffer;

    memcpy(eth->h_dest, dest, ETH_ALEN);
    memcpy(eth->h_source, sm->ownaddr, ETH_ALEN);
    eth->h_proto = host_to_be16(proto);

    wps_sendto_wrapper(buffer, sizeof(struct l2_ethhdr) + data_len);

    return ESP_OK;
}