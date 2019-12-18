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
struct mode_data {int dummy; } ;
typedef  enum requirement { ____Placeholder_requirement } requirement ;

/* Variables and functions */
 int /*<<< orphan*/  bytesize ; 
 int /*<<< orphan*/  component ; 
 int /*<<< orphan*/  format ; 
 int /*<<< orphan*/  ncomponents ; 
 int /*<<< orphan*/  precision ; 
 int /*<<< orphan*/  validate_field (struct mode_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
validate_mode (struct mode_data *m,
	       enum requirement r_precision,
	       enum requirement r_bytesize,
	       enum requirement r_component,
	       enum requirement r_ncomponents,
	       enum requirement r_format)
{
  validate_field (m, precision);
  validate_field (m, bytesize);
  validate_field (m, component);
  validate_field (m, ncomponents);
  validate_field (m, format);
}