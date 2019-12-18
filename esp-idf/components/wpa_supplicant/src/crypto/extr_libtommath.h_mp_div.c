#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_1__ ;

/* Type definitions */
struct TYPE_38__ {int sign; } ;
typedef  TYPE_1__ mp_int ;

/* Variables and functions */
 scalar_t__ MP_GT ; 
 scalar_t__ MP_LT ; 
 int MP_NEG ; 
 int MP_OKAY ; 
 int MP_VAL ; 
 int MP_YES ; 
 int MP_ZPOS ; 
 int mp_abs (TYPE_1__*,TYPE_1__*) ; 
 int mp_add (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  mp_clear_multi (TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ mp_cmp (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ mp_cmp_mag (TYPE_1__*,TYPE_1__*) ; 
 int mp_copy (TYPE_1__*,TYPE_1__*) ; 
 int mp_count_bits (TYPE_1__*) ; 
 int mp_div_2d (TYPE_1__*,int,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_exch (TYPE_1__*,TYPE_1__*) ; 
 int mp_init_multi (TYPE_1__*,TYPE_1__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int mp_iszero (TYPE_1__*) ; 
 int mp_mul_2d (TYPE_1__*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  mp_set (TYPE_1__*,int) ; 
 int mp_sub (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  mp_zero (TYPE_1__*) ; 

__attribute__((used)) static int 
mp_div(mp_int * a, mp_int * b, mp_int * c, mp_int * d)
{
   mp_int ta, tb, tq, q;
   int    res, n, n2;

  /* is divisor zero ? */
  if (mp_iszero (b) == 1) {
    return MP_VAL;
  }

  /* if a < b then q=0, r = a */
  if (mp_cmp_mag (a, b) == MP_LT) {
    if (d != NULL) {
      res = mp_copy (a, d);
    } else {
      res = MP_OKAY;
    }
    if (c != NULL) {
      mp_zero (c);
    }
    return res;
  }
	
  /* init our temps */
  if ((res = mp_init_multi(&ta, &tb, &tq, &q, NULL) != MP_OKAY)) {
     return res;
  }


  mp_set(&tq, 1);
  n = mp_count_bits(a) - mp_count_bits(b);
  if (((res = mp_abs(a, &ta)) != MP_OKAY) ||
      ((res = mp_abs(b, &tb)) != MP_OKAY) || 
      ((res = mp_mul_2d(&tb, n, &tb)) != MP_OKAY) ||
      ((res = mp_mul_2d(&tq, n, &tq)) != MP_OKAY)) {
      goto LBL_ERR;
  }

  while (n-- >= 0) {
     if (mp_cmp(&tb, &ta) != MP_GT) {
        if (((res = mp_sub(&ta, &tb, &ta)) != MP_OKAY) ||
            ((res = mp_add(&q, &tq, &q)) != MP_OKAY)) {
           goto LBL_ERR;
        }
     }
     if (((res = mp_div_2d(&tb, 1, &tb, NULL)) != MP_OKAY) ||
         ((res = mp_div_2d(&tq, 1, &tq, NULL)) != MP_OKAY)) {
           goto LBL_ERR;
     }
  }

  /* now q == quotient and ta == remainder */
  n  = a->sign;
  n2 = (a->sign == b->sign ? MP_ZPOS : MP_NEG);
  if (c != NULL) {
     mp_exch(c, &q);
     c->sign  = (mp_iszero(c) == MP_YES) ? MP_ZPOS : n2;
  }
  if (d != NULL) {
     mp_exch(d, &ta);
     d->sign = (mp_iszero(d) == MP_YES) ? MP_ZPOS : n;
  }
LBL_ERR:
   mp_clear_multi(&ta, &tb, &tq, &q, NULL);
   return res;
}