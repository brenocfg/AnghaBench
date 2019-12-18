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
struct TYPE_3__ {int member_3; int member_4; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ curve_params ;

/* Variables and functions */
 int BR_EC_secp256r1 ; 
#define  P256_B 136 
#define  P256_P 135 
#define  P256_R2 134 
#define  P384_B 133 
#define  P384_P 132 
#define  P384_R2 131 
#define  P521_B 130 
#define  P521_P 129 
#define  P521_R2 128 

__attribute__((used)) static inline const curve_params *
id_to_curve(int curve)
{
	static const curve_params pp[] = {
		{ P256_P, P256_B, P256_R2, 0x0001,  65 },
		{ P384_P, P384_B, P384_R2, 0x0001,  97 },
		{ P521_P, P521_B, P521_R2, 0x0001, 133 }
	};

	return &pp[curve - BR_EC_secp256r1];
}