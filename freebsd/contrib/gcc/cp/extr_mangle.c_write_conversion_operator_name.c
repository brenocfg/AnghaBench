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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  write_string (char*) ; 
 int /*<<< orphan*/  write_type (int /*<<< orphan*/  const) ; 

__attribute__((used)) static void
write_conversion_operator_name (const tree type)
{
  write_string ("cv");
  write_type (type);
}