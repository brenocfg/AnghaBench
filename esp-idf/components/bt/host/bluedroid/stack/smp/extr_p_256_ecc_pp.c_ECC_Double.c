#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/ * z; int /*<<< orphan*/ * y; int /*<<< orphan*/ * x; } ;
typedef  TYPE_1__ Point ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int KEY_LENGTH_DWORDS_P256 ; 
 int /*<<< orphan*/  multiprecision_add_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multiprecision_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ multiprecision_iszero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multiprecision_lshift_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multiprecision_mersenns_mult_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multiprecision_mersenns_squa_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multiprecision_sub_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ECC_Double(Point *q, Point *p, uint32_t keyLength)
{
    DWORD t1[KEY_LENGTH_DWORDS_P256];
    DWORD t2[KEY_LENGTH_DWORDS_P256];
    DWORD t3[KEY_LENGTH_DWORDS_P256];
    DWORD *x1;
    DWORD *x3;
    DWORD *y1;
    DWORD *y3;
    DWORD *z1;
    DWORD *z3;

    if (multiprecision_iszero(p->z, keyLength)) {
        multiprecision_init(q->z, keyLength);
        return;                                     // return infinity
    }

    x1 = p->x; y1 = p->y; z1 = p->z;
    x3 = q->x; y3 = q->y; z3 = q->z;

    multiprecision_mersenns_squa_mod(t1, z1, keyLength);  // t1=z1^2
    multiprecision_sub_mod(t2, x1, t1, keyLength);  // t2=x1-t1
    multiprecision_add_mod(t1, x1, t1, keyLength);  // t1=x1+t1
    multiprecision_mersenns_mult_mod(t2, t1, t2, keyLength);  // t2=t2*t1
    multiprecision_lshift_mod(t3, t2, keyLength);
    multiprecision_add_mod(t2, t3, t2, keyLength);  // t2=3t2

    multiprecision_mersenns_mult_mod(z3, y1, z1, keyLength);  // z3=y1*z1
    multiprecision_lshift_mod(z3, z3, keyLength);

    multiprecision_mersenns_squa_mod(y3, y1, keyLength);  // y3=y1^2
    multiprecision_lshift_mod(y3, y3, keyLength);
    multiprecision_mersenns_mult_mod(t3, y3, x1, keyLength);  // t3=y3*x1=x1*y1^2
    multiprecision_lshift_mod(t3, t3, keyLength);
    multiprecision_mersenns_squa_mod(y3, y3, keyLength);  // y3=y3^2=y1^4
    multiprecision_lshift_mod(y3, y3, keyLength);

    multiprecision_mersenns_squa_mod(x3, t2, keyLength);  // x3=t2^2
    multiprecision_lshift_mod(t1, t3, keyLength);                // t1=2t3
    multiprecision_sub_mod(x3, x3, t1, keyLength);               // x3=x3-t1
    multiprecision_sub_mod(t1, t3, x3, keyLength);               // t1=t3-x3
    multiprecision_mersenns_mult_mod(t1, t1, t2, keyLength);  // t1=t1*t2
    multiprecision_sub_mod(y3, t1, y3, keyLength);               // y3=t1-y3
}