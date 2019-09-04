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
typedef  int /*<<< orphan*/  int16x8 ;

/* Variables and functions */
 int emscripten_int16x8_extractLane (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char const*,int,int,int,int,int,int,int,int) ; 

void dump(const char *name, int16x8 vec)
{
    printf("%s: %d %d %d %d %d %d %d %d\n", name, emscripten_int16x8_extractLane(vec, 0), emscripten_int16x8_extractLane(vec, 1), emscripten_int16x8_extractLane(vec, 2), emscripten_int16x8_extractLane(vec, 3),
        emscripten_int16x8_extractLane(vec, 4), emscripten_int16x8_extractLane(vec, 5), emscripten_int16x8_extractLane(vec, 6), emscripten_int16x8_extractLane(vec, 7));
}