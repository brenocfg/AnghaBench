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
typedef  int /*<<< orphan*/  float32x4 ;
typedef  int /*<<< orphan*/  bytes ;
typedef  int /*<<< orphan*/  bool32x4 ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DUMPBYTES (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emscripten_float32x4_abs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float32x4_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float32x4_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float32x4_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float32x4_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double emscripten_float32x4_extractLane (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emscripten_float32x4_greaterThan (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float32x4_greaterThanOrEqual (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float32x4_lessThan (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float32x4_lessThanOrEqual (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float32x4_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emscripten_float32x4_load1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emscripten_float32x4_load2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emscripten_float32x4_max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float32x4_maxNum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float32x4_min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float32x4_minNum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float32x4_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float32x4_neg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float32x4_not (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float32x4_notEqual (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float32x4_or (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float32x4_reciprocalApproximation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float32x4_reciprocalSqrtApproximation (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float32x4_replaceLane (int /*<<< orphan*/ ,int,float) ; 
 int /*<<< orphan*/  emscripten_float32x4_select (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float32x4_set (float,float,float,float) ; 
 int /*<<< orphan*/  emscripten_float32x4_shuffle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  emscripten_float32x4_splat (float) ; 
 int /*<<< orphan*/  emscripten_float32x4_sqrt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float32x4_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float32x4_store1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float32x4_store2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float32x4_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_float32x4_swizzle (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  emscripten_float32x4_xor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_int32x4_set (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 double fabs (double) ; 
 int isinf (double) ; 
 int isnan (double) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 double sqrt (double) ; 

int main()
{
    float32x4 v = emscripten_float32x4_set(-1.f, 0.f, 1.f, 3.5f);
    DUMP(v);
    float32x4 w = emscripten_float32x4_splat(2.f);
    DUMP(w);
    DUMP(emscripten_float32x4_add(v, w));
    DUMP(emscripten_float32x4_sub(v, w));
    DUMP(emscripten_float32x4_mul(v, w));
    DUMP(emscripten_float32x4_div(v, w));
    DUMP(emscripten_float32x4_max(v, w));
    DUMP(emscripten_float32x4_min(v, w));
    DUMP(emscripten_float32x4_maxNum(v, w));
    DUMP(emscripten_float32x4_minNum(v, w));
    DUMP(emscripten_float32x4_neg(v));
    DUMP(emscripten_float32x4_sqrt(v));
    float32x4 rcp = emscripten_float32x4_reciprocalApproximation(v);
    assert(fabs(emscripten_float32x4_extractLane(rcp, 0) - 1.0 / emscripten_float32x4_extractLane(v, 0)) < 0.1);
    assert(isinf(emscripten_float32x4_extractLane(rcp, 1)));
    assert(fabs(emscripten_float32x4_extractLane(rcp, 2) - 1.0 / emscripten_float32x4_extractLane(v, 2)) < 0.1);
    assert(fabs(emscripten_float32x4_extractLane(rcp, 3) - 1.0 / emscripten_float32x4_extractLane(v, 3)) < 0.1);
    float32x4 rcpSqrt = emscripten_float32x4_reciprocalSqrtApproximation(v);
    assert(isnan(emscripten_float32x4_extractLane(rcpSqrt, 0)));
    assert(isinf(emscripten_float32x4_extractLane(rcpSqrt, 1)));
    assert(fabs(emscripten_float32x4_extractLane(rcpSqrt, 2) - 1.0 / sqrt(emscripten_float32x4_extractLane(v, 2))) < 0.1);
    assert(fabs(emscripten_float32x4_extractLane(rcpSqrt, 3) - 1.0 / sqrt(emscripten_float32x4_extractLane(v, 3))) < 0.1);
    DUMP(emscripten_float32x4_abs(v));
    DUMP(emscripten_float32x4_and(v, w));
    DUMP(emscripten_float32x4_xor(v, w));
    DUMP(emscripten_float32x4_or(v, w));
    DUMP(emscripten_float32x4_not(v));
    DUMP(emscripten_float32x4_lessThan(v, w));
    DUMP(emscripten_float32x4_lessThanOrEqual(v, w));
    DUMP(emscripten_float32x4_greaterThan(v, w));
    DUMP(emscripten_float32x4_greaterThanOrEqual(v, w));
    DUMP(emscripten_float32x4_equal(v, w));
    DUMP(emscripten_float32x4_notEqual(v, w));
    bool32x4 b = emscripten_int32x4_set(0, -1, 0, -1);
    DUMP(emscripten_float32x4_select(b, v, w));
    DUMP(emscripten_float32x4_replaceLane(v, 0, 9.f));
    DUMP(emscripten_float32x4_replaceLane(v, 1, -3.f));
    DUMP(emscripten_float32x4_replaceLane(v, 2, 0.f));
    DUMP(emscripten_float32x4_replaceLane(v, 3, -0.f));
    uint8_t bytes[16];
    memset(bytes, 0xFF, sizeof(bytes));
    emscripten_float32x4_store(bytes, v);
    DUMPBYTES("emscripten_float32x4_store", bytes);
    memset(bytes, 0xFF, sizeof(bytes));
    emscripten_float32x4_store1(bytes, v);
    DUMPBYTES("emscripten_float32x4_store1", bytes);
    memset(bytes, 0xFF, sizeof(bytes));
    emscripten_float32x4_store2(bytes, v);
    DUMPBYTES("emscripten_float32x4_store2", bytes);

    emscripten_float32x4_store(bytes, v);
    DUMP(emscripten_float32x4_load(bytes));
    DUMP(emscripten_float32x4_load1(bytes));
    DUMP(emscripten_float32x4_load2(bytes));
    // TODO: emscripten_float32x4_fromFloat64x2Bits
    // TODO: emscripten_float32x4_fromInt32x4Bits
    // TODO: emscripten_float32x4_fromUint32x4Bits
    // TODO: emscripten_float32x4_fromInt16x8Bits
    // TODO: emscripten_float32x4_fromUint16x8Bits
    // TODO: emscripten_float32x4_fromInt8x16Bits
    // TODO: emscripten_float32x4_fromUint8x16Bits
    // TODO: emscripten_float32x4_fromInt32x4
    // TODO: emscripten_float32x4_fromUint32x4
    DUMP(emscripten_float32x4_swizzle(v, 0, 1, 2, 3));
    DUMP(emscripten_float32x4_swizzle(v, 3, 2, 1, 0));
    DUMP(emscripten_float32x4_swizzle(v, 0, 0, 0, 0));
    DUMP(emscripten_float32x4_swizzle(v, 0, 3, 0, 3));
    DUMP(emscripten_float32x4_swizzle(v, 3, 3, 3, 3));
    float32x4 z = emscripten_float32x4_set(-5.f, 20.f, 14.f, 9.f);
    DUMP(z);
    DUMP(emscripten_float32x4_shuffle(v, z, 0, 0, 0, 0));
    DUMP(emscripten_float32x4_shuffle(v, z, 4, 4, 4, 4));
    DUMP(emscripten_float32x4_shuffle(v, z, 7, 7, 7, 7));
    DUMP(emscripten_float32x4_shuffle(v, z, 0, 2, 4, 6));
    DUMP(emscripten_float32x4_shuffle(v, z, 7, 0, 3, 5));

    printf("Done!\n");
}