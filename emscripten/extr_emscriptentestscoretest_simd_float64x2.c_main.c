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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  float64x2 ;
typedef  int /*<<< orphan*/  bytes ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DUMPBYTES (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emscripten_float64x2_abs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float64x2_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float64x2_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float64x2_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float64x2_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double emscripten_float64x2_extractLane (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emscripten_float64x2_greaterThan (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float64x2_greaterThanOrEqual (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float64x2_lessThan (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float64x2_lessThanOrEqual (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float64x2_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emscripten_float64x2_load1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emscripten_float64x2_max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float64x2_maxNum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float64x2_min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float64x2_minNum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float64x2_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float64x2_neg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float64x2_not (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float64x2_notEqual (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float64x2_or (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float64x2_reciprocalApproximation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float64x2_reciprocalSqrtApproximation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float64x2_replaceLane (int /*<<< orphan*/ ,int,float) ; 
 int /*<<< orphan*/  emscripten_float64x2_set (float,float) ; 
 int /*<<< orphan*/  emscripten_float64x2_shuffle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  emscripten_float64x2_splat (float) ; 
 int /*<<< orphan*/  emscripten_float64x2_sqrt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float64x2_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float64x2_store1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float64x2_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float64x2_swizzle (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  emscripten_float64x2_xor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double fabs (double) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 double sqrt (double) ; 

int main()
{
    float64x2 v = emscripten_float64x2_set(-1.5f, 2.5f);
    DUMP(v);
    float64x2 w = emscripten_float64x2_splat(1.5f);
    DUMP(w);
    DUMP(emscripten_float64x2_add(v, w));
    DUMP(emscripten_float64x2_sub(v, w));
    DUMP(emscripten_float64x2_mul(v, w));
    DUMP(emscripten_float64x2_div(v, w));
    DUMP(emscripten_float64x2_max(v, w));
    DUMP(emscripten_float64x2_min(v, w));
    DUMP(emscripten_float64x2_maxNum(v, w));
    DUMP(emscripten_float64x2_minNum(v, w));
    DUMP(emscripten_float64x2_neg(v));
    DUMP(emscripten_float64x2_sqrt(v));
    float64x2 rcp = emscripten_float64x2_reciprocalApproximation(v);
    assert(fabs(emscripten_float64x2_extractLane(rcp, 0) - 1.0 / emscripten_float64x2_extractLane(v, 0)) < 0.1);
    assert(fabs(emscripten_float64x2_extractLane(rcp, 1) - 1.0 / emscripten_float64x2_extractLane(v, 1)) < 0.1);
    float64x2 rcpSqrt = emscripten_float64x2_reciprocalSqrtApproximation(v);
    // assert(isnan(emscripten_float64x2_extractLane(rcpSqrt, 0))); XXX TODO Enable once Float64x2 type lands in SIMD.js.
    assert(fabs(emscripten_float64x2_extractLane(rcpSqrt, 1) - 1.0 / sqrt(emscripten_float64x2_extractLane(v, 1))) < 0.1);
    DUMP(emscripten_float64x2_abs(v));
    DUMP(emscripten_float64x2_and(v, w));
    DUMP(emscripten_float64x2_xor(v, w));
    DUMP(emscripten_float64x2_or(v, w));
    DUMP(emscripten_float64x2_not(v));
    DUMP(emscripten_float64x2_lessThan(v, w));
    DUMP(emscripten_float64x2_lessThanOrEqual(v, w));
    DUMP(emscripten_float64x2_greaterThan(v, w));
    DUMP(emscripten_float64x2_greaterThanOrEqual(v, w));
    DUMP(emscripten_float64x2_equal(v, w));
    DUMP(emscripten_float64x2_notEqual(v, w));
    //bool64x2 b = emscripten_int64x2_set(0, -1); // TODO: Can't yet use this form, no int64x2.
    //DUMP(emscripten_float64x2_select(b, v, w));
    DUMP(emscripten_float64x2_replaceLane(v, 0, 9.f));
    DUMP(emscripten_float64x2_replaceLane(v, 1, -3.f));
    uint8_t bytes[16];
    memset(bytes, 0xFF, sizeof(bytes));
    emscripten_float64x2_store(bytes, v);
    DUMPBYTES("emscripten_float64x2_store", bytes);
    memset(bytes, 0xFF, sizeof(bytes));
    emscripten_float64x2_store1(bytes, v);
    DUMPBYTES("emscripten_float64x2_store1", bytes);

    emscripten_float64x2_store(bytes, v);
    DUMP(emscripten_float64x2_load(bytes));
    DUMP(emscripten_float64x2_load1(bytes));
    // TODO: emscripten_float64x2_fromFloat64x2Bits
    // TODO: emscripten_float64x2_fromInt64x2Bits
    // TODO: emscripten_float64x2_fromUint64x2Bits
    // TODO: emscripten_float64x2_fromInt16x8Bits
    // TODO: emscripten_float64x2_fromUint16x8Bits
    // TODO: emscripten_float64x2_fromInt8x16Bits
    // TODO: emscripten_float64x2_fromUint8x16Bits
    // TODO: emscripten_float64x2_fromInt64x2
    // TODO: emscripten_float64x2_fromUint64x2
    DUMP(emscripten_float64x2_swizzle(v, 0, 1));
    DUMP(emscripten_float64x2_swizzle(v, 1, 0));
    DUMP(emscripten_float64x2_swizzle(v, 0, 0));
    DUMP(emscripten_float64x2_swizzle(v, 1, 1));
    float64x2 z = emscripten_float64x2_set(-5.5f, 20.5f);
    DUMP(z);
    DUMP(emscripten_float64x2_shuffle(v, z, 0, 0));
    DUMP(emscripten_float64x2_shuffle(v, z, 2, 2));
    DUMP(emscripten_float64x2_shuffle(v, z, 3, 3));
    DUMP(emscripten_float64x2_shuffle(v, z, 0, 2));
    DUMP(emscripten_float64x2_shuffle(v, z, 3, 1));

    printf("Done!\n");
}