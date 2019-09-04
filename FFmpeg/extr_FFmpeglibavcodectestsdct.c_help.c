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

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void help(void)
{
    printf("dct-test [-i] [<test-number>] [<bits>]\n"
           "test-number 0 -> test with random matrixes\n"
           "            1 -> test with random sparse matrixes\n"
           "            2 -> do 3. test from MPEG-4 std\n"
           "bits        Number of time domain bits to use, 8 is default\n"
           "-i          test IDCT implementations\n"
           "-4          test IDCT248 implementations\n"
           "-t          speed test\n");
}