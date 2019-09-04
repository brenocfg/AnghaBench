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
struct ResampleContext {int dummy; } ;
typedef  int /*<<< orphan*/  soxr_t ;
typedef  scalar_t__ soxr_error_t ;
struct TYPE_4__ {int /*<<< orphan*/  ch; int /*<<< orphan*/  ch_count; } ;
typedef  TYPE_1__ AudioData ;

/* Variables and functions */
 scalar_t__ soxr_process (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,size_t*,int /*<<< orphan*/ ,size_t,size_t*) ; 
 scalar_t__ soxr_set_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soxr_set_num_channels (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int process(
        struct ResampleContext * c, AudioData *dst, int dst_size,
        AudioData *src, int src_size, int *consumed){
    size_t idone, odone;
    soxr_error_t error = soxr_set_error((soxr_t)c, soxr_set_num_channels((soxr_t)c, src->ch_count));
    if (!error)
        error = soxr_process((soxr_t)c, src->ch, (size_t)src_size,
                             &idone, dst->ch, (size_t)dst_size, &odone);
    else
        idone = 0;

    *consumed = (int)idone;
    return error? -1 : odone;
}