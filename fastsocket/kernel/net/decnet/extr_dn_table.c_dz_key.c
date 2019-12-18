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
struct dn_zone {int dummy; } ;
struct TYPE_3__ {int datum; } ;
typedef  TYPE_1__ dn_fib_key_t ;
typedef  int __le16 ;

/* Variables and functions */
 int DZ_MASK (struct dn_zone*) ; 

__attribute__((used)) static inline dn_fib_key_t dz_key(__le16 dst, struct dn_zone *dz)
{
	dn_fib_key_t k;
	k.datum = dst & DZ_MASK(dz);
	return k;
}