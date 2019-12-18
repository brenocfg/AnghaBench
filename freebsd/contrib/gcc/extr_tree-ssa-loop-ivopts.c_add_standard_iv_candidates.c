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
struct ivopts_data {int dummy; } ;

/* Variables and functions */
 int BITS_PER_WORD ; 
 int INT_TYPE_SIZE ; 
 int /*<<< orphan*/  add_standard_iv_candidates_for_size (struct ivopts_data*,int) ; 

__attribute__((used)) static void
add_standard_iv_candidates (struct ivopts_data *data)
{
  add_standard_iv_candidates_for_size (data, INT_TYPE_SIZE);

  /* The same for a double-integer type if it is still fast enough.  */
  if (BITS_PER_WORD >= INT_TYPE_SIZE * 2)
    add_standard_iv_candidates_for_size (data, INT_TYPE_SIZE * 2);
}