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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
 scalar_t__ SIS635A_900_REV ; 
 scalar_t__ SIS900B_900_REV ; 
 int ether_crc (int,scalar_t__*) ; 

__attribute__((used)) static inline u16 sis900_mcast_bitnr(u8 *addr, u8 revision)
{

	u32 crc = ether_crc(6, addr);

	/* leave 8 or 7 most siginifant bits */
	if ((revision >= SIS635A_900_REV) || (revision == SIS900B_900_REV))
		return ((int)(crc >> 24));
	else
		return ((int)(crc >> 25));
}