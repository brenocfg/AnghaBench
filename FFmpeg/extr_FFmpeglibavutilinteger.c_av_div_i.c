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
typedef  int /*<<< orphan*/  AVInteger ;

/* Variables and functions */
 int /*<<< orphan*/  av_mod_i (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

AVInteger av_div_i(AVInteger a, AVInteger b){
    AVInteger quot;
    av_mod_i(&quot, a, b);
    return quot;
}