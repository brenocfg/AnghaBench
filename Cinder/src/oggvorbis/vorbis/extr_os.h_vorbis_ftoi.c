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
 int _mm_cvtsd_si32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mm_load_sd (double*) ; 

__attribute__((used)) static __inline int vorbis_ftoi(double f){
        return _mm_cvtsd_si32(_mm_load_sd(&f));
}