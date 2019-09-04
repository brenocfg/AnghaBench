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
 int /*<<< orphan*/  printf (char*,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float) ; 

__attribute__((used)) static void printMatrix(float* m) {
    printf("{%f, %f, %f, %f,\n"
           " %f, %f, %f, %f,\n"
           " %f, %f, %f, %f,\n"
           " %f, %f, %f, %f}\n",
           m[0],  m[1],  m[2],  m[3],
           m[4],  m[5],  m[6],  m[7],
           m[8],  m[9],  m[10], m[11],
           m[12], m[13], m[14], m[15]);
}