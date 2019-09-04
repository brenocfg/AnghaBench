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
typedef  int /*<<< orphan*/  float32x4 ;

/* Variables and functions */
 int /*<<< orphan*/  emscripten_float32x4_extractLane (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printFloat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void dump(const char *name, float32x4 vec)
{
    printf("%s: ", name);
    printFloat(emscripten_float32x4_extractLane(vec, 0));
    printf(" ");
    printFloat(emscripten_float32x4_extractLane(vec, 1));
    printf(" ");
    printFloat(emscripten_float32x4_extractLane(vec, 2));
    printf(" ");
    printFloat(emscripten_float32x4_extractLane(vec, 3));
    printf("\n");
}