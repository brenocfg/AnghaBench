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
typedef  int /*<<< orphan*/  AudioData ;

/* Variables and functions */

__attribute__((used)) static int invert_initial_buffer(struct ResampleContext *c, AudioData *dst, const AudioData *src,
                                 int in_count, int *out_idx, int *out_sz){
    return 0;
}