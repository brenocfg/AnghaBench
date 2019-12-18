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
struct efx_filter_spec {int* data; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void __efx_filter_set_ipv4(struct efx_filter_spec *spec,
					 __be32 host1, __be16 port1,
					 __be32 host2, __be16 port2)
{
	spec->data[0] = ntohl(host1) << 16 | ntohs(port1);
	spec->data[1] = ntohs(port2) << 16 | ntohl(host1) >> 16;
	spec->data[2] = ntohl(host2);
}