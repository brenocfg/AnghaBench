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
struct representation {int /*<<< orphan*/  cur_timestamp; int /*<<< orphan*/  init_sec_data_len; int /*<<< orphan*/  init_sec_buf_size; int /*<<< orphan*/  init_sec_buf; int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_mallocz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int copy_init_section(struct representation *rep_dest, struct representation *rep_src)
{
    rep_dest->init_sec_buf = av_mallocz(rep_src->init_sec_buf_size);
    if (!rep_dest->init_sec_buf) {
        av_log(rep_dest->ctx, AV_LOG_WARNING, "Cannot alloc memory for init_sec_buf\n");
        return AVERROR(ENOMEM);
    }
    memcpy(rep_dest->init_sec_buf, rep_src->init_sec_buf, rep_src->init_sec_data_len);
    rep_dest->init_sec_buf_size = rep_src->init_sec_buf_size;
    rep_dest->init_sec_data_len = rep_src->init_sec_data_len;
    rep_dest->cur_timestamp = rep_src->cur_timestamp;

    return 0;
}