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

/* Variables and functions */
 int /*<<< orphan*/  frag_more (int) ; 
 int /*<<< orphan*/  md_number_to_chars (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline void
out_four (int data)
{
  md_number_to_chars (frag_more (4), data, 4);
}