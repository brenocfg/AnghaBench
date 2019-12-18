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
 int occupied (float*,int) ; 

__attribute__((used)) static int makes_safe_go(float *b, int *lib, int p, int r, int c){
    if (r < 0 || r >= 19 || c < 0 || c >= 19) return 0;
    if (occupied(b,r*19 + c) == -p){
        if (lib[r*19 + c] > 1) return 0;
        else return 1;
    }
    if (!occupied(b,r*19 + c)) return 1;
    if (lib[r*19 + c] > 1) return 1;
    return 0;
}