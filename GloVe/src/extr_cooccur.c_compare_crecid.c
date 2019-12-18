#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int word1; int word2; } ;
typedef  TYPE_1__ CRECID ;

/* Variables and functions */

int compare_crecid(CRECID a, CRECID b) {
    int c;
    if ( (c = a.word1 - b.word1) != 0) return c;
    else return a.word2 - b.word2;
}