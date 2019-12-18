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
typedef  int /*<<< orphan*/  u32 ;
struct sh_eth_private {int edmac_endian; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
#define  EDMAC_BIG_ENDIAN 129 
#define  EDMAC_LITTLE_ENDIAN 128 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline __u32 cpu_to_edmac(struct sh_eth_private *mdp, u32 x)
{
	switch (mdp->edmac_endian) {
	case EDMAC_LITTLE_ENDIAN:
		return cpu_to_le32(x);
	case EDMAC_BIG_ENDIAN:
		return cpu_to_be32(x);
	}
	return x;
}