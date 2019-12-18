#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {int /*<<< orphan*/ * z; int /*<<< orphan*/ * y; int /*<<< orphan*/ * x; } ;
typedef  TYPE_1__ Point ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ECC_Double (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int KEY_LENGTH_DWORDS_P256 ; 
 int /*<<< orphan*/  multiprecision_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ multiprecision_iszero (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multiprecision_lshift_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multiprecision_mersenns_mult_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multiprecision_mersenns_squa_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  multiprecision_sub_mod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_256_copy_point (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static void ECC_Add(Point *r, Point *p, Point *q, uint32_t keyLength)
{
    DWORD t1[KEY_LENGTH_DWORDS_P256];
    DWORD t2[KEY_LENGTH_DWORDS_P256];
    DWORD *x1;
    DWORD *x2;
    DWORD *x3;
    DWORD *y1;
    DWORD *y2;
    DWORD *y3;
    DWORD *z1;
    DWORD *z2;
    DWORD *z3;

    x1 = p->x; y1 = p->y; z1 = p->z;
    x2 = q->x; y2 = q->y; z2 = q->z;
    x3 = r->x; y3 = r->y; z3 = r->z;

    // if Q=infinity, return p
    if (multiprecision_iszero(z2, keyLength)) {
        p_256_copy_point(r, p);
        return;
    }

    // if P=infinity, return q
    if (multiprecision_iszero(z1, keyLength)) {
        p_256_copy_point(r, q);
        return;
    }

    multiprecision_mersenns_squa_mod(t1, z1, keyLength);      // t1=z1^2
    multiprecision_mersenns_mult_mod(t2, z1, t1, keyLength);  // t2=t1*z1
    multiprecision_mersenns_mult_mod(t1, x2, t1, keyLength);  // t1=t1*x2
    multiprecision_mersenns_mult_mod(t2, y2, t2, keyLength);  // t2=t2*y2

    multiprecision_sub_mod(t1, t1, x1, keyLength);  // t1=t1-x1
    multiprecision_sub_mod(t2, t2, y1, keyLength);  // t2=t2-y1

    if (multiprecision_iszero(t1, keyLength)) {
        if (multiprecision_iszero(t2, keyLength)) {
            ECC_Double(r, q, keyLength) ;
            return;
        } else {
            multiprecision_init(z3, keyLength);
            return;                             // return infinity
        }
    }

    multiprecision_mersenns_mult_mod(z3, z1, t1, keyLength);  // z3=z1*t1
    multiprecision_mersenns_squa_mod(y3, t1, keyLength);      // t3=t1^2
    multiprecision_mersenns_mult_mod(z1, y3, t1, keyLength);  // t4=t3*t1
    multiprecision_mersenns_mult_mod(y3, y3, x1, keyLength);  // t3=t3*x1
    multiprecision_lshift_mod(t1, y3, keyLength);            // t1=2*t3
    multiprecision_mersenns_squa_mod(x3, t2, keyLength);      // x3=t2^2
    multiprecision_sub_mod(x3, x3, t1, keyLength);           // x3=x3-t1
    multiprecision_sub_mod(x3, x3, z1, keyLength);           // x3=x3-t4
    multiprecision_sub_mod(y3, y3, x3, keyLength);           // t3=t3-x3
    multiprecision_mersenns_mult_mod(y3, y3, t2, keyLength);  // t3=t3*t2
    multiprecision_mersenns_mult_mod(z1, z1, y1, keyLength);  // t4=t4*t1
    multiprecision_sub_mod(y3, y3, z1, keyLength);
}