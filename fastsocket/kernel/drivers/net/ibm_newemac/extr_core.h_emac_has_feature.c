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
struct emac_instance {unsigned long features; } ;

/* Variables and functions */
 unsigned long EMAC_FTRS_ALWAYS ; 
 unsigned long EMAC_FTRS_POSSIBLE ; 

__attribute__((used)) static inline int emac_has_feature(struct emac_instance *dev,
				   unsigned long feature)
{
	return (EMAC_FTRS_ALWAYS & feature) ||
	       (EMAC_FTRS_POSSIBLE & dev->features & feature);
}