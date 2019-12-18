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
struct ResampleContext {int dummy; } ;
typedef  int /*<<< orphan*/  soxr_t ;

/* Variables and functions */
 int /*<<< orphan*/  soxr_delete (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy(struct ResampleContext * *c){
    soxr_delete((soxr_t)*c);
    *c = NULL;
}