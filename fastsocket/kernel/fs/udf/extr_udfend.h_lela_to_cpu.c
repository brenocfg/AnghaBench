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
struct long_ad {int /*<<< orphan*/  extLocation; int /*<<< orphan*/  extLength; } ;
struct kernel_long_ad {int /*<<< orphan*/  extLocation; int /*<<< orphan*/  extLength; } ;

/* Variables and functions */
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lelb_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct kernel_long_ad lela_to_cpu(struct long_ad in)
{
	struct kernel_long_ad out;

	out.extLength = le32_to_cpu(in.extLength);
	out.extLocation = lelb_to_cpu(in.extLocation);

	return out;
}