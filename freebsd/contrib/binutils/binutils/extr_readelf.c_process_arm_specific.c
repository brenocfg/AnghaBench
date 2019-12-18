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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SHT_ARM_ATTRIBUTES ; 
 int /*<<< orphan*/  display_arm_attribute ; 
 int process_attributes (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
process_arm_specific (FILE *file)
{
  return process_attributes (file, "aeabi", SHT_ARM_ATTRIBUTES,
			     display_arm_attribute, NULL);
}