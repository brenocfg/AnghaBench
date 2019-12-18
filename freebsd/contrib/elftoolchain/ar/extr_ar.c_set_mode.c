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
struct bsdar {char mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  bsdar_errc (struct bsdar*,int /*<<< orphan*/ ,char*,char,char) ; 

__attribute__((used)) static void
set_mode(struct bsdar *bsdar, char opt)
{

	if (bsdar->mode != '\0' && bsdar->mode != opt)
		bsdar_errc(bsdar, 0, "Can't specify both -%c and -%c",
		    opt, bsdar->mode);
	bsdar->mode = opt;
}