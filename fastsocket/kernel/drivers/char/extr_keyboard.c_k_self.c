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
struct vc_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  conv_8bit_to_uni (unsigned char) ; 
 int /*<<< orphan*/  k_unicode (struct vc_data*,int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static void k_self(struct vc_data *vc, unsigned char value, char up_flag)
{
	k_unicode(vc, conv_8bit_to_uni(value), up_flag);
}