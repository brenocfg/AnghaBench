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
 int* A ; 
 int* B ; 
 size_t j ; 
 size_t k ; 
 size_t m ; 
 size_t n ; 
 int x ; 

f5(){
	x=A[k*m]*A[j*m]+B[k*n]*B[j*n];
	x=A[k*m]*B[j*n]-B[k*n]*A[j*m];
}