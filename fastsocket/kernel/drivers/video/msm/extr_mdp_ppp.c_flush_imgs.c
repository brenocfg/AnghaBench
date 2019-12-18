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
struct mdp_regs {int dummy; } ;
struct mdp_blit_req {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void flush_imgs(struct mdp_blit_req *req, struct mdp_regs *regs,
		       struct file *src_file, struct file *dst_file)
{
}