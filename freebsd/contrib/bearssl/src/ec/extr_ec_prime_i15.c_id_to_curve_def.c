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
typedef  int /*<<< orphan*/  br_ec_curve_def ;

/* Variables and functions */
#define  BR_EC_secp256r1 130 
#define  BR_EC_secp384r1 129 
#define  BR_EC_secp521r1 128 
 int /*<<< orphan*/  const br_secp256r1 ; 
 int /*<<< orphan*/  const br_secp384r1 ; 
 int /*<<< orphan*/  const br_secp521r1 ; 

__attribute__((used)) static const br_ec_curve_def *
id_to_curve_def(int curve)
{
	switch (curve) {
	case BR_EC_secp256r1:
		return &br_secp256r1;
	case BR_EC_secp384r1:
		return &br_secp384r1;
	case BR_EC_secp521r1:
		return &br_secp521r1;
	}
	return NULL;
}