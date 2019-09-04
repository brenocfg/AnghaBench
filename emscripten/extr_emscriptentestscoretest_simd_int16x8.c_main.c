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
typedef  void* int16x8 ;
typedef  int /*<<< orphan*/  bytes ;
typedef  void* bool32x4 ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP (void*) ; 
 int /*<<< orphan*/  DUMPBYTES (char*,int /*<<< orphan*/ *) ; 
 void* emscripten_int16x8_add (void*,void*) ; 
 void* emscripten_int16x8_addSaturate (void*,void*) ; 
 void* emscripten_int16x8_and (void*,void*) ; 
 void* emscripten_int16x8_equal (void*,void*) ; 
 void* emscripten_int16x8_greaterThan (void*,void*) ; 
 void* emscripten_int16x8_greaterThanOrEqual (void*,void*) ; 
 void* emscripten_int16x8_lessThan (void*,void*) ; 
 void* emscripten_int16x8_lessThanOrEqual (void*,void*) ; 
 void* emscripten_int16x8_load (int /*<<< orphan*/ *) ; 
 void* emscripten_int16x8_mul (void*,void*) ; 
 void* emscripten_int16x8_neg (void*) ; 
 void* emscripten_int16x8_not (void*) ; 
 void* emscripten_int16x8_notEqual (void*,void*) ; 
 void* emscripten_int16x8_or (void*,void*) ; 
 void* emscripten_int16x8_replaceLane (void*,int,int) ; 
 void* emscripten_int16x8_select (void*,void*,void*) ; 
 void* emscripten_int16x8_set (int,int,int,int,int,int,int,int) ; 
 void* emscripten_int16x8_shiftLeftByScalar (void*,int) ; 
 void* emscripten_int16x8_shiftRightByScalar (void*,int) ; 
 void* emscripten_int16x8_shuffle (void*,void*,int,int,int,int,int,int,int,int) ; 
 void* emscripten_int16x8_splat (int) ; 
 int /*<<< orphan*/  emscripten_int16x8_store (int /*<<< orphan*/ *,void*) ; 
 void* emscripten_int16x8_sub (void*,void*) ; 
 void* emscripten_int16x8_subSaturate (void*,void*) ; 
 void* emscripten_int16x8_swizzle (void*,int,int,int,int,int,int,int,int) ; 
 void* emscripten_int16x8_xor (void*,void*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

int main()
{
    int16x8 v = emscripten_int16x8_set(1, 0, 1, 32767, -2, 9, 13, -32768);
    DUMP(v);
    int16x8 w = emscripten_int16x8_splat(2);
    DUMP(w);
    DUMP(emscripten_int16x8_add(v, w));
    DUMP(emscripten_int16x8_sub(v, w));
    DUMP(emscripten_int16x8_mul(v, w));
    DUMP(emscripten_int16x8_neg(v));
    DUMP(emscripten_int16x8_and(v, w));
    DUMP(emscripten_int16x8_xor(v, w));
    DUMP(emscripten_int16x8_or(v, w));
    DUMP(emscripten_int16x8_not(v));
    DUMP(emscripten_int16x8_lessThan(v, w));
    DUMP(emscripten_int16x8_lessThanOrEqual(v, w));
    DUMP(emscripten_int16x8_greaterThan(v, w));
    DUMP(emscripten_int16x8_greaterThanOrEqual(v, w));
    DUMP(emscripten_int16x8_equal(v, w));
    DUMP(emscripten_int16x8_notEqual(v, w));
//    DUMPINT(emscripten_int16x8_anyTrue(v)); // XXX TODO: Figure out if there is a no-op cast from int16x8->bool16x8 and enable this, or remove if this doesn't make sense.
//    DUMPINT(emscripten_int16x8_allTrue(v)); // XXX TODO: Figure out if there is a no-op cast from int16x8->bool16x8 and enable this, or remove if this doesn't make sense.
    DUMP(emscripten_int16x8_shiftLeftByScalar(v, 0));
    DUMP(emscripten_int16x8_shiftLeftByScalar(v, 1));
    DUMP(emscripten_int16x8_shiftLeftByScalar(v, 2));
    DUMP(emscripten_int16x8_shiftLeftByScalar(v, 16));
    DUMP(emscripten_int16x8_shiftLeftByScalar(v, 32));
    DUMP(emscripten_int16x8_shiftLeftByScalar(v, 48));
    DUMP(emscripten_int16x8_shiftRightByScalar(v, 0));
    DUMP(emscripten_int16x8_shiftRightByScalar(v, 1));
    DUMP(emscripten_int16x8_shiftRightByScalar(v, 2));
    DUMP(emscripten_int16x8_shiftRightByScalar(v, 16));
    DUMP(emscripten_int16x8_shiftRightByScalar(v, 32));
    DUMP(emscripten_int16x8_shiftRightByScalar(v, 48));
    bool32x4 b = emscripten_int16x8_set(0, -1, 0, -1, 0, -1, 0, -1);
    DUMP(emscripten_int16x8_select(b, v, w));
    DUMP(emscripten_int16x8_addSaturate(v, w));
    DUMP(emscripten_int16x8_subSaturate(v, w));
    DUMP(emscripten_int16x8_replaceLane(v, 0, 9));
    DUMP(emscripten_int16x8_replaceLane(v, 1, 3));
    DUMP(emscripten_int16x8_replaceLane(v, 2, 0));
    DUMP(emscripten_int16x8_replaceLane(v, 3, 91));
    DUMP(emscripten_int16x8_replaceLane(v, 4, 32767));
    DUMP(emscripten_int16x8_replaceLane(v, 5, 100));
    DUMP(emscripten_int16x8_replaceLane(v, 6, -100));
    DUMP(emscripten_int16x8_replaceLane(v, 7, -32768));
    uint8_t bytes[16];
    memset(bytes, 0xFF, sizeof(bytes));
    emscripten_int16x8_store(bytes, v);
    DUMPBYTES("emscripten_int16x8_store", bytes);
    DUMP(emscripten_int16x8_load(bytes));
    // TODO: emscripten_int16x8_fromFloat64x2Bits
    // TODO: emscripten_int16x8_fromint16x8Bits
    // TODO: emscripten_int16x8_fromUint16x8Bits
    // TODO: emscripten_int16x8_fromInt16x8Bits
    // TODO: emscripten_int16x8_fromUint16x8Bits
    // TODO: emscripten_int16x8_fromInt8x16Bits
    // TODO: emscripten_int16x8_fromUint8x16Bits
    // TODO: emscripten_int16x8_fromint16x8
    // TODO: emscripten_int16x8_fromUint16x8
    DUMP(emscripten_int16x8_swizzle(v, 0, 1, 2, 3, 4, 5, 6, 7));
    DUMP(emscripten_int16x8_swizzle(v, 7, 6, 5, 4, 3, 2, 1, 0));
    DUMP(emscripten_int16x8_swizzle(v, 0, 0, 0, 0, 0, 0, 0, 0));
    DUMP(emscripten_int16x8_swizzle(v, 0, 3, 0, 3, 7, 1, 2, 6));
    DUMP(emscripten_int16x8_swizzle(v, 3, 3, 3, 3, 3, 3, 3, 3));
    int16x8 z = emscripten_int16x8_set(-5, 20, 14, 9, 0, 11, 32764, -32750);
    DUMP(z);
    DUMP(emscripten_int16x8_shuffle(v, z, 0, 0, 0, 0, 0, 0, 0, 0));
    DUMP(emscripten_int16x8_shuffle(v, z, 4, 4, 4, 4, 4, 4, 4, 4));
    DUMP(emscripten_int16x8_shuffle(v, z, 15, 15, 15, 15, 7, 7, 7, 7));
    DUMP(emscripten_int16x8_shuffle(v, z, 0, 2, 4, 6, 8, 10, 12, 14));
    DUMP(emscripten_int16x8_shuffle(v, z, 7, 0, 3, 5, 9, 11, 1, 4));
    printf("Done!\n");
}