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
typedef  void* int32x4 ;
typedef  int /*<<< orphan*/  bytes ;
typedef  void* bool32x4 ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP (void*) ; 
 int /*<<< orphan*/  DUMPBYTES (char*,int /*<<< orphan*/ *) ; 
 void* emscripten_int32x4_add (void*,void*) ; 
 void* emscripten_int32x4_and (void*,void*) ; 
 void* emscripten_int32x4_equal (void*,void*) ; 
 void* emscripten_int32x4_greaterThan (void*,void*) ; 
 void* emscripten_int32x4_greaterThanOrEqual (void*,void*) ; 
 void* emscripten_int32x4_lessThan (void*,void*) ; 
 void* emscripten_int32x4_lessThanOrEqual (void*,void*) ; 
 void* emscripten_int32x4_load (int /*<<< orphan*/ *) ; 
 void* emscripten_int32x4_load1 (int /*<<< orphan*/ *) ; 
 void* emscripten_int32x4_load2 (int /*<<< orphan*/ *) ; 
 void* emscripten_int32x4_mul (void*,void*) ; 
 void* emscripten_int32x4_neg (void*) ; 
 void* emscripten_int32x4_not (void*) ; 
 void* emscripten_int32x4_notEqual (void*,void*) ; 
 void* emscripten_int32x4_or (void*,void*) ; 
 void* emscripten_int32x4_replaceLane (void*,int,int) ; 
 void* emscripten_int32x4_select (void*,void*,void*) ; 
 void* emscripten_int32x4_set (int,int,int,int) ; 
 void* emscripten_int32x4_shiftLeftByScalar (void*,int) ; 
 void* emscripten_int32x4_shiftRightByScalar (void*,int) ; 
 void* emscripten_int32x4_shuffle (void*,void*,int,int,int,int) ; 
 void* emscripten_int32x4_splat (int) ; 
 int /*<<< orphan*/  emscripten_int32x4_store (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  emscripten_int32x4_store1 (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  emscripten_int32x4_store2 (int /*<<< orphan*/ *,void*) ; 
 void* emscripten_int32x4_sub (void*,void*) ; 
 void* emscripten_int32x4_swizzle (void*,int,int,int,int) ; 
 void* emscripten_int32x4_xor (void*,void*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

int main()
{
    int32x4 v = emscripten_int32x4_set(1, 0, 1, 4);
    DUMP(v);
    int32x4 w = emscripten_int32x4_splat(2);
    DUMP(w);
    DUMP(emscripten_int32x4_add(v, w));
    DUMP(emscripten_int32x4_sub(v, w));
    DUMP(emscripten_int32x4_mul(v, w));
    DUMP(emscripten_int32x4_neg(v));
    DUMP(emscripten_int32x4_and(v, w));
    DUMP(emscripten_int32x4_xor(v, w));
    DUMP(emscripten_int32x4_or(v, w));
    DUMP(emscripten_int32x4_not(v));
    DUMP(emscripten_int32x4_lessThan(v, w));
    DUMP(emscripten_int32x4_lessThanOrEqual(v, w));
    DUMP(emscripten_int32x4_greaterThan(v, w));
    DUMP(emscripten_int32x4_greaterThanOrEqual(v, w));
    DUMP(emscripten_int32x4_equal(v, w));
    DUMP(emscripten_int32x4_notEqual(v, w));
//    DUMPINT(emscripten_int32x4_anyTrue(v)); // XXX TODO: Figure out if there is a no-op cast from int32x4->bool32x4 and enable this, or remove if this doesn't make sense.
//    DUMPINT(emscripten_int32x4_allTrue(v)); // XXX TODO: Figure out if there is a no-op cast from int32x4->bool32x4 and enable this, or remove if this doesn't make sense.
    DUMP(emscripten_int32x4_shiftLeftByScalar(v, 0));
    DUMP(emscripten_int32x4_shiftLeftByScalar(v, 1));
    DUMP(emscripten_int32x4_shiftLeftByScalar(v, 2));
    DUMP(emscripten_int32x4_shiftLeftByScalar(v, 16));
    DUMP(emscripten_int32x4_shiftLeftByScalar(v, 32));
    DUMP(emscripten_int32x4_shiftLeftByScalar(v, 48));
    DUMP(emscripten_int32x4_shiftRightByScalar(v, 0));
    DUMP(emscripten_int32x4_shiftRightByScalar(v, 1));
    DUMP(emscripten_int32x4_shiftRightByScalar(v, 2));
    DUMP(emscripten_int32x4_shiftRightByScalar(v, 16));
    DUMP(emscripten_int32x4_shiftRightByScalar(v, 32));
    DUMP(emscripten_int32x4_shiftRightByScalar(v, 48));
    bool32x4 b = emscripten_int32x4_set(0, -1, 0, -1);
    DUMP(emscripten_int32x4_select(b, v, w));
    DUMP(emscripten_int32x4_replaceLane(v, 0, 9));
    DUMP(emscripten_int32x4_replaceLane(v, 1, 3));
    DUMP(emscripten_int32x4_replaceLane(v, 2, 0));
    DUMP(emscripten_int32x4_replaceLane(v, 3, 91));
    uint8_t bytes[16];
    memset(bytes, 0xFF, sizeof(bytes));
    emscripten_int32x4_store(bytes, v);
    DUMPBYTES("emscripten_int32x4_store", bytes);
    memset(bytes, 0xFF, sizeof(bytes));
    emscripten_int32x4_store1(bytes, v);
    DUMPBYTES("emscripten_int32x4_store1", bytes);
    memset(bytes, 0xFF, sizeof(bytes));
    emscripten_int32x4_store2(bytes, v);
    DUMPBYTES("emscripten_int32x4_store2", bytes);

    emscripten_int32x4_store(bytes, v);
    DUMP(emscripten_int32x4_load(bytes));
    DUMP(emscripten_int32x4_load1(bytes));
    DUMP(emscripten_int32x4_load2(bytes));
    // TODO: emscripten_int32x4_fromFloat64x2Bits
    // TODO: emscripten_int32x4_fromInt32x4Bits
    // TODO: emscripten_int32x4_fromUint32x4Bits
    // TODO: emscripten_int32x4_fromInt16x8Bits
    // TODO: emscripten_int32x4_fromUint16x8Bits
    // TODO: emscripten_int32x4_fromInt8x16Bits
    // TODO: emscripten_int32x4_fromUint8x16Bits
    // TODO: emscripten_int32x4_fromInt32x4
    // TODO: emscripten_int32x4_fromUint32x4
    DUMP(emscripten_int32x4_swizzle(v, 0, 1, 2, 3));
    DUMP(emscripten_int32x4_swizzle(v, 3, 2, 1, 0));
    DUMP(emscripten_int32x4_swizzle(v, 0, 0, 0, 0));
    DUMP(emscripten_int32x4_swizzle(v, 0, 3, 0, 3));
    DUMP(emscripten_int32x4_swizzle(v, 3, 3, 3, 3));
    int32x4 z = emscripten_int32x4_set(-5, 20, 14, 9);
    DUMP(z);
    DUMP(emscripten_int32x4_shuffle(v, z, 0, 0, 0, 0));
    DUMP(emscripten_int32x4_shuffle(v, z, 4, 4, 4, 4));
    DUMP(emscripten_int32x4_shuffle(v, z, 7, 7, 7, 7));
    DUMP(emscripten_int32x4_shuffle(v, z, 0, 2, 4, 6));
    DUMP(emscripten_int32x4_shuffle(v, z, 7, 0, 3, 5));
    printf("Done!\n");
}