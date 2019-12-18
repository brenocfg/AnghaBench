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
typedef  int /*<<< orphan*/  offsetT ;

/* Variables and functions */
 int /*<<< orphan*/  frag_more (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_leb128 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sizeof_leb128 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
out_sleb128 (offsetT value)
{
  output_leb128 (frag_more (sizeof_leb128 (value, 1)), value, 1);
}