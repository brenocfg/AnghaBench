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
typedef  int /*<<< orphan*/  regexp_t ;

/* Variables and functions */
 int /*<<< orphan*/  regexp_transform_func (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ regexp_transformed_p ; 
 int /*<<< orphan*/  transform_1 ; 
 int /*<<< orphan*/  transform_2 ; 
 int /*<<< orphan*/  transform_3 ; 

__attribute__((used)) static regexp_t
transform_regexp (regexp_t regexp)
{
  regexp = regexp_transform_func (regexp, transform_1);
  do
    {
      regexp_transformed_p = 0;
      regexp = regexp_transform_func (regexp, transform_2);
      regexp = regexp_transform_func (regexp, transform_3);
    }
  while (regexp_transformed_p);
  return regexp;
}