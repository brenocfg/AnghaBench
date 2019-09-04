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

__attribute__((used)) static void remove_connected(float *b, int *lib, int p, int r, int c)
{
    if (r < 0 || r >= 19 || c < 0 || c >= 19) return;
    if (occupied(b, r*19 + c) != p) return;
    if (lib[r*19 + c] != 1) return;
    b[r*19 + c] = 0;
    b[19*19 + r*19 + c] = 0;
    remove_connected(b, lib, p, r+1, c);
    remove_connected(b, lib, p, r-1, c);
    remove_connected(b, lib, p, r, c+1);
    remove_connected(b, lib, p, r, c-1);
}