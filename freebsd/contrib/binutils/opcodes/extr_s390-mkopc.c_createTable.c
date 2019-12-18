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
struct op_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  malloc (int) ; 
 int max_ops ; 
 scalar_t__ no_ops ; 
 int /*<<< orphan*/  op_array ; 

__attribute__((used)) static void
createTable (void)
{
  max_ops = 256;
  op_array = malloc (max_ops * sizeof (struct op_struct));
  no_ops = 0;
}