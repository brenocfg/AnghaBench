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
struct gfs2_log_descriptor {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */

__attribute__((used)) static inline struct gfs2_log_descriptor *bh_log_desc(struct buffer_head *bh)
{
	return (struct gfs2_log_descriptor *)bh->b_data;
}