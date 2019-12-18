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
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  htons (int) ; 

__attribute__((used)) static inline void __efx_filter_get_ipv4(const struct efx_filter_spec *spec,
					 __be32 *host1, __be16 *port1,
					 __be32 *host2, __be16 *port2)
{
	*host1 = htonl(spec->data[0] >> 16 | spec->data[1] << 16);
	*port1 = htons(spec->data[0]);
	*host2 = htonl(spec->data[2]);
	*port2 = htons(spec->data[1] >> 16);
}