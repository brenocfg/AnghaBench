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
typedef  int real ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isinf (int) ; 
 scalar_t__ isnan (int) ; 
 int /*<<< orphan*/  stderr ; 

inline real check_nan(real update) {
    if (isnan(update) || isinf(update)) {
        fprintf(stderr,"\ncaught NaN in update");
        return 0.;
    } else {
        return update;
    }
}