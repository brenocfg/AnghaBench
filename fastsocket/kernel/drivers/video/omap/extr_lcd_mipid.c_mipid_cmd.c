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
struct mipid_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mipid_transfer (struct mipid_device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mipid_cmd(struct mipid_device *md, int cmd)
{
	mipid_transfer(md, cmd, NULL, 0, NULL, 0);
}