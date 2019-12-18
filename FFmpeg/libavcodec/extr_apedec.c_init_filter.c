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
typedef  int /*<<< orphan*/  int16_t ;
typedef  int /*<<< orphan*/  APEFilter ;
typedef  int /*<<< orphan*/  APEContext ;

/* Variables and functions */
 int HISTORY_SIZE ; 
 int /*<<< orphan*/  do_init_filter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void init_filter(APEContext *ctx, APEFilter *f, int16_t *buf, int order)
{
    do_init_filter(&f[0], buf, order);
    do_init_filter(&f[1], buf + order * 3 + HISTORY_SIZE, order);
}