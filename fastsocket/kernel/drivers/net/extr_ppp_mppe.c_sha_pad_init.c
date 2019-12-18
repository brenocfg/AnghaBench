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
struct sha_pad {int /*<<< orphan*/  sha_pad2; int /*<<< orphan*/  sha_pad1; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline void sha_pad_init(struct sha_pad *shapad)
{
	memset(shapad->sha_pad1, 0x00, sizeof(shapad->sha_pad1));
	memset(shapad->sha_pad2, 0xF2, sizeof(shapad->sha_pad2));
}