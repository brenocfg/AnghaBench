#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  naf ;
typedef  int UINT8 ;
struct TYPE_16__ {int /*<<< orphan*/ * p; } ;
struct TYPE_15__ {int /*<<< orphan*/ * p; } ;
struct TYPE_14__ {int* z; int* x; int* y; } ;
typedef  TYPE_1__ Point ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ECC_Add (TYPE_1__*,TYPE_1__*,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  ECC_Double (TYPE_1__*,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  ECC_NAF (int*,scalar_t__*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ KEY_LENGTH_DWORDS_P256 ; 
 TYPE_6__ curve ; 
 TYPE_5__ curve_p256 ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  multiprecision_copy (int*,int*,scalar_t__) ; 
 int /*<<< orphan*/  multiprecision_init (int*,scalar_t__) ; 
 int /*<<< orphan*/  multiprecision_inv_mod (int*,int*,scalar_t__) ; 
 int /*<<< orphan*/  multiprecision_mersenns_mult_mod (int*,int*,int*,scalar_t__) ; 
 int /*<<< orphan*/  multiprecision_mersenns_squa_mod (int*,int*,scalar_t__) ; 
 int /*<<< orphan*/  multiprecision_sub (int*,int /*<<< orphan*/ *,int*,scalar_t__) ; 
 int /*<<< orphan*/  p_256_copy_point (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  p_256_init_point (TYPE_1__*) ; 

void ECC_PointMult_Bin_NAF(Point *q, Point *p, DWORD *n, uint32_t keyLength)
{
    uint32_t sign;
    UINT8 naf[256 / 4 + 1];
    uint32_t NumNaf;
    Point minus_p;
    Point r;
    DWORD *modp;

    if (keyLength == KEY_LENGTH_DWORDS_P256) {
        modp = curve_p256.p;
    } else {
        modp = curve.p;
    }

    p_256_init_point(&r);
    multiprecision_init(p->z, keyLength);
    p->z[0] = 1;

    // initialization
    p_256_init_point(q);

    // -p
    multiprecision_copy(minus_p.x, p->x, keyLength);
    multiprecision_sub(minus_p.y, modp, p->y, keyLength);

    multiprecision_init(minus_p.z, keyLength);
    minus_p.z[0] = 1;

    // NAF
    memset(naf, 0, sizeof(naf));
    ECC_NAF(naf, &NumNaf, n, keyLength);

    for (int i = NumNaf - 1; i >= 0; i--) {
        p_256_copy_point(&r, q);
        ECC_Double(q, &r, keyLength);
        sign = (naf[i / 4] >> ((i % 4) * 2)) & 0x03;

        if (sign == 1) {
            p_256_copy_point(&r, q);
            ECC_Add(q, &r, p, keyLength);
        } else if (sign == 3) {
            p_256_copy_point(&r, q);
            ECC_Add(q, &r, &minus_p, keyLength);
        }
    }

    multiprecision_inv_mod(minus_p.x, q->z, keyLength);
    multiprecision_mersenns_squa_mod(q->z, minus_p.x, keyLength);
    multiprecision_mersenns_mult_mod(q->x, q->x, q->z, keyLength);
    multiprecision_mersenns_mult_mod(q->z, q->z, minus_p.x, keyLength);
    multiprecision_mersenns_mult_mod(q->y, q->y, q->z, keyLength);
}